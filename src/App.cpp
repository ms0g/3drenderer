#include "App.h"
#include <SDL2/SDL.h>
#include "ObjParser.h"
#include "MeshData.hpp"
#include "../libs/imgui/imgui_impl_sdl.h"


App::App(const char* objFile, const char* textureFile) {
    // Create Graphics
    graphics = std::make_unique<Graphics>();

    // Open Window
    isRunning = graphics->OpenWindow();

    // Create gui
    gui = std::make_unique<Gui>(graphics->GetSDLWindow(), graphics->GetSDLRenderer());

    // Perspective Matrix
    projectionMatrix = mat4::PerspectiveMatrix(FOV_Y, ASPECT_Y, ZNEAR, ZFAR);

    // Render settings
    settings.cullMethod = CullMethod::CULL_BACKFACE;
    settings.renderMethod = RenderMethod::RENDER_TEXTURED;

    // Load Mesh
    auto meshData = ObjParser::Load(objFile);
    mesh.SetData(meshData);

    // Load texture
    auto texture = std::make_unique<Texture>(textureFile);
    mesh.SetTexture(texture);

    // Initialize frustum planes
    frustum.InitializePlanes();
}


bool App::IsRunning() const {
    return isRunning;
}


void App::Input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        ImGuiIO& io = ImGui::GetIO();

        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.MousePos = ImVec2(mouseX, mouseY);
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    isRunning = false;
                if (event.key.keysym.sym == SDLK_UP)
                    camera.UpdatePosition({0.0, static_cast<float>(3.0 * deltaTime), 0.0});
                if (event.key.keysym.sym == SDLK_DOWN)
                    camera.UpdatePosition({0.0, -static_cast<float>(3.0 * deltaTime), 0.0});
                if (event.key.keysym.sym == SDLK_a)
                    camera.UpdateYaw(-1.0 * deltaTime);
                if (event.key.keysym.sym == SDLK_d)
                    camera.UpdateYaw(1.0 * deltaTime);
                if (event.key.keysym.sym == SDLK_w) {
                    camera.SetForwardVelocity(camera.GetDirection() * 5.0 * deltaTime);
                    camera.SetPosition(camera.GetPosition() + camera.GetForwardVelocity());
                }
                if (event.key.keysym.sym == SDLK_s) {
                    camera.SetForwardVelocity(camera.GetDirection() * 5.0 * deltaTime);
                    camera.SetPosition(camera.GetPosition() - camera.GetForwardVelocity());
                }
                break;
        }
    }
}


void App::Update() {
    auto timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(timeToWait);

    deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    millisecsPreviousFrame = SDL_GetTicks();

    mesh.UpdateRotation({static_cast<float>(0.0 * deltaTime),
                         static_cast<float>(0.0 * deltaTime),
                         static_cast<float>(0.0 * deltaTime)});
    // Translate the mesh away from the camera
    mesh.SetTranslation({0.0, 0.0, 5.0});

    // Initialize the target positive z-axis
    vec3 target = {0, 0, 1};

    mat4 cameraYawRotation = mat4::RotationMatrixY(camera.GetYaw());
    vec3 direction = vec3::FromVec4(cameraYawRotation * vec4::FromVec3(target));
    camera.SetDirection(direction);

    // Offset the camera position in the direction where the camera is pointing at
    target = camera.GetPosition() + camera.GetDirection();

    vec3 up = {0, 1, 0};
    // Create the view matrix
    mat4 viewMatrix = mat4::LookAt(camera.GetPosition(), target, up);

    // Create scale matrix that will be used to multiply the mesh vertices;
    mat4 scaleMatrix = mat4::ScaleMatrix(mesh.GetScale().x, mesh.GetScale().y, mesh.GetScale().z);

    mat4 translationMatrix = mat4::TranslationMatrix(mesh.GetTranslation().x,
                                                     mesh.GetTranslation().y,
                                                     mesh.GetTranslation().z);

    mat4 rotationXMatrix = mat4::RotationMatrixX(mesh.GetRotation().x);
    mat4 rotationYMatrix = mat4::RotationMatrixY(mesh.GetRotation().y);
    mat4 rotationZMatrix = mat4::RotationMatrixZ(mesh.GetRotation().z);


    for (const auto& meshFace: mesh.GetFaces()) {
        vec3 faceVertices[3];
        faceVertices[0] = mesh.GetVertices()[meshFace.a];
        faceVertices[1] = mesh.GetVertices()[meshFace.b];
        faceVertices[2] = mesh.GetVertices()[meshFace.c];

        vec4 transformedVertices[3];
        // Loop all three vertices of this current face and apply transformations
        for (int i = 0; i < 3; ++i) {
            vec4 transformedVertex = vec4::FromVec3(faceVertices[i]);

            // Create a World Matrix combining scale, rotation, and translation matrices
            mat4 worldMatrix = mat4::IdentityMatrix();

            // Order matters: First scale, then rotate, then translate. [T]*[R]*[S]*v
            worldMatrix = scaleMatrix * worldMatrix;
            worldMatrix = rotationZMatrix * worldMatrix;
            worldMatrix = rotationYMatrix * worldMatrix;
            worldMatrix = rotationXMatrix * worldMatrix;
            worldMatrix = translationMatrix * worldMatrix;

            transformedVertex = worldMatrix * transformedVertex;
            transformedVertex = viewMatrix * transformedVertex;

            transformedVertices[i] = transformedVertex;
        }

        // Check backface culling
        vec3 vecA = vec3::FromVec4(transformedVertices[0]);     /*    A    */
        vec3 vecB = vec3::FromVec4(transformedVertices[1]);     /*  /   \  */
        vec3 vecC = vec3::FromVec4(transformedVertices[2]);     /* C-----B */

        // Get the vector subtraction of B-A and C-A
        vec3 ab = vecB - vecA;
        vec3 ac = vecC - vecA;
        ab.Normalize();
        ac.Normalize();

        // Compute the face normal
        vec3 normal = ab.Cross(ac);
        normal.Normalize();

        // Find the vector between a point in the triangle and camera origin
        vec3 origin = {0, 0, 0};
        vec3 cameraRay = origin - vecA;

        // Calculate how aligned the normal onto the camera ray
        float dotNormalCamera = normal.Dot(cameraRay);
        if (settings.cullMethod == CullMethod::CULL_BACKFACE) {
            // Bypass the triangles that are looking away the camera
            if (dotNormalCamera < 0) {
                continue;
            }
        }

        // Clipping Process
        polygon_t polygon = polygon_t::FromTriangle(
                vec3::FromVec4(transformedVertices[0]),
                vec3::FromVec4(transformedVertices[1]),
                vec3::FromVec4(transformedVertices[2]),
                meshFace.a_uv,
                meshFace.b_uv,
                meshFace.c_uv);

        frustum.StartClipping(polygon);

        // Break the clipped polygon apart back into individual triangles
        Triangle trianglesAfterClipping[MAX_NUM_POLY_TRIANGLES];
        int numTrianglesAfterClipping = 0;

        polygon_t::TrianglesFromPolygon(polygon, trianglesAfterClipping, numTrianglesAfterClipping);

        // Loops all the assembled triangles after clipping
        for (auto& triangleAfterClipping: trianglesAfterClipping) {
            Triangle projectedTriangle;
            // Loop all three vertices to perform projection
            for (int i = 0; i < 3; ++i) {
                // Project the current vertex
                vec4 projectedPoint = projectionMatrix * triangleAfterClipping.points[i];

                // Perform perspective divide with original z-value stored in w
                if (projectedPoint.w != 0.0) {
                    projectedPoint.x /= projectedPoint.w;
                    projectedPoint.y /= projectedPoint.w;
                    projectedPoint.z /= projectedPoint.w;
                }
                // Scale into the view
                projectedPoint.x *= (WINDOW_WIDTH / 2.0);
                projectedPoint.y *= (WINDOW_HEIGHT / 2.0);

                // Invert the y value to fix upside-down object rendering
                projectedPoint.y *= -1;

                // Translate the projected points to the middle of the screen
                projectedPoint.x += (WINDOW_WIDTH / 2.0);
                projectedPoint.y += (WINDOW_HEIGHT / 2.0);

                projectedTriangle.points[i] = {projectedPoint.x, projectedPoint.y, projectedPoint.z, projectedPoint.w};
            }

            projectedTriangle.texcoords[0] = triangleAfterClipping.texcoords[0];
            projectedTriangle.texcoords[1] = triangleAfterClipping.texcoords[1];
            projectedTriangle.texcoords[2] = triangleAfterClipping.texcoords[2];

            // Calculate the shade intensity
            float lightIntensityFactor = -light.direction.Dot(normal);
            uint32_t triangleColor = Light::ApplyLightIntensity(meshFace.color, lightIntensityFactor);

            projectedTriangle.color = triangleColor;

            trianglesToRender.push_back(projectedTriangle);
        }
    }
}


void App::Render() {
    graphics->RenderClear();

    graphics->DrawGrid();

    // Loop all projected triangles and render them
    for (auto& triangle: trianglesToRender) {
        // Draw filled triangle
        if (graphics->ShouldRenderFilledTriangle(settings)) {
            graphics->DrawFilledTriangle(
                    triangle.points[0].x, triangle.points[0].y, triangle.points[0].z, triangle.points[0].w,
                    triangle.points[1].x, triangle.points[1].y, triangle.points[1].z, triangle.points[1].w,
                    triangle.points[2].x, triangle.points[2].y, triangle.points[2].z, triangle.points[2].w,
                    triangle.color
            );
        }

        // Draw textured triangle
        if (graphics->ShouldRenderTexturedTriangle(settings)) {
            graphics->DrawTexturedTriangle(
                    triangle.points[0].x, triangle.points[0].y, triangle.points[0].z, triangle.points[0].w,
                    triangle.texcoords[0],
                    triangle.points[1].x, triangle.points[1].y, triangle.points[1].z, triangle.points[1].w,
                    triangle.texcoords[1],
                    triangle.points[2].x, triangle.points[2].y, triangle.points[2].z, triangle.points[2].w,
                    triangle.texcoords[2],
                    mesh.GetTexture()
            );
        }

        // Draw triangle wireframe
        if (graphics->ShouldRenderWireFrame(settings)) {
            graphics->DrawTriangle(
                    triangle.points[0].x, triangle.points[0].y,
                    triangle.points[1].x, triangle.points[1].y,
                    triangle.points[2].x, triangle.points[2].y,
                    0xFFFFFFFF
            );
        }

        if (graphics->ShouldRenderWireVertex(settings)) {
            graphics->DrawRect(triangle.points[0].x - 3, triangle.points[0].y, 6, 6, 0xFFFF0000);
            graphics->DrawRect(triangle.points[1].x - 3, triangle.points[1].y, 6, 6, 0xFFFF0000);
            graphics->DrawRect(triangle.points[2].x - 3, triangle.points[2].y, 6, 6, 0xFFFF0000);
        }
    }

    trianglesToRender.clear();

    graphics->UpdateColorBuffer();
    gui->Render(settings);

    graphics->ClearColorBuffer(0xFF000000);
    graphics->ClearDepthBuffer();

    graphics->RenderPresent();
}