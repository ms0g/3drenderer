#include "Renderer.h"
#include <iostream>
#include "ObjParser.h"
#include "Graphics.h"
#include "Gui.h"
#include "MeshData.hpp"
#include "Vec4.h"
#include "Mat4.h"

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    window = SDL_CreateWindow(
            nullptr,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            displayMode.w,
            displayMode.h,
            SDL_WINDOW_BORDERLESS);

    if (!window) {
        std::cerr << "Error creating SDL Window";
        return;
    }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL Renderer" << std::endl;
        return;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE);

    // Camera settings
    cameraPos = {0, 0, 0};

    // Perspective Matrix
    projectionMatrix = Mat4::PerspectiveMatrix(FOV, ASPECT, ZNEAR, ZFAR);

    // Create color buffer
    graphics = std::make_unique<Graphics>(renderer);

    // Create Gui
    gui = std::make_unique<Gui>(window, renderer);

    // Render settings
    settings.cullMethod = CullMethod::CULL_BACKFACE;
    settings.renderMethod = RenderMethod::RENDER_FILL_TRIANGLE;
}


Renderer::~Renderer() {
    // Clean up SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Renderer::LoadMesh(const char* objFile) {
    //auto meshData = ObjParser::Load(objFile);
    auto meshData = ObjParser::load_cube_mesh_data();
    mesh.SetData(meshData);
    mesh.texture = (uint32_t*)REDBRICK_TEXTURE;
}

void Renderer::Update() {
    auto timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(timeToWait);

    millisecsPreviousFrame = SDL_GetTicks();

    mesh.SetRotation(Vec3{0.0,0.01,0.0});
    // Translate the mesh away from the camera
    mesh.SetTranslation(Vec3{0.0,0.0,5.0});

    // Create scale matrix that will be used to multiply the mesh vertices;
    Mat4 scaleMatrix = Mat4::ScaleMatrix(mesh.GetScale().x, mesh.GetScale().y, mesh.GetScale().z);

    Mat4 translationMatrix = Mat4::TranslationMatrix(mesh.GetTranslation().x,
                                                     mesh.GetTranslation().y,
                                                     mesh.GetTranslation().z);

    Mat4 rotationXMatrix = Mat4::RotationXMatrix(mesh.GetRotation().x);
    Mat4 rotationYMatrix = Mat4::RotationYMatrix(mesh.GetRotation().y);
    Mat4 rotationZMatrix = Mat4::RotationZMatrix(mesh.GetRotation().z);


    for (const auto& meshFace: mesh.GetFaces()) {
        Vec3 faceVertices[3];
        faceVertices[0] = mesh.GetVertices()[meshFace.a - 1];
        faceVertices[1] = mesh.GetVertices()[meshFace.b - 1];
        faceVertices[2] = mesh.GetVertices()[meshFace.c - 1];

        Vec4 transformedVertices[3];
        // Loop all three vertices of this current face and apply transformations
        for (int i = 0; i < 3; ++i) {
            Vec4 transformedVertex = Vec4::FromVec3(faceVertices[i]);

            // Create a World Matrix combining scale, rotation, and translation matrices
            Mat4 worldMatrix = Mat4::IdentityMatrix();

            // Order matters: First scale, then rotate, then translate. [T]*[R]*[S]*v
            worldMatrix = scaleMatrix * worldMatrix;
            worldMatrix = rotationZMatrix * worldMatrix;
            worldMatrix = rotationYMatrix * worldMatrix;
            worldMatrix = rotationXMatrix * worldMatrix;
            worldMatrix = translationMatrix * worldMatrix;

            transformedVertex = worldMatrix * transformedVertex;

            transformedVertices[i] = transformedVertex;
        }

        // Check backface culling
        Vec3 vecA = Vec3::FromVec4(transformedVertices[0]);     /*    A    */
        Vec3 vecB = Vec3::FromVec4(transformedVertices[1]);     /*  /   \  */
        Vec3 vecC = Vec3::FromVec4(transformedVertices[2]);     /* C-----B */

        // Get the vector subtraction of B-A and C-A
        Vec3 ab = vecB - vecA;
        Vec3 ac = vecC - vecA;
        ab.Normalize();
        ac.Normalize();

        // Compute the face normal
        Vec3 normal = ab.Cross(ac);
        normal.Normalize();

        // Find the vector between a point in the triangle and camera origin
        Vec3 cameraRay = cameraPos - vecA;

        // Calculate how aligned the normal onto the camera ray
        float dotNormalCamera = normal.Dot(cameraRay);
        if (settings.cullMethod == CullMethod::CULL_BACKFACE) {
            // Bypass the triangles that are looking away the camera
            if (dotNormalCamera < 0) {
                continue;
            }
        }

        Triangle projectedTriangle;
        // Loop all three vertices to perform projection
        for (int i = 0; i < 3; ++i) {
            // Project the current vertex
            Vec4 projectedPoint = projectionMatrix * transformedVertices[i];

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

            projectedTriangle.points[i] = {projectedPoint.x, projectedPoint.y};
        }

        projectedTriangle.texcoords[0] = {meshFace.a_uv.u, meshFace.a_uv.v};
        projectedTriangle.texcoords[1] = {meshFace.b_uv.u, meshFace.b_uv.v};
        projectedTriangle.texcoords[2] = {meshFace.c_uv.u, meshFace.c_uv.v};


        // Calculate the shade intensity
        float lightIntensityFactor = -light.direction.Dot(normal);

        uint32_t triangleColor = Light::ApplyLightIntensity(meshFace.color, lightIntensityFactor);
        projectedTriangle.color = triangleColor;

        //TODO:remove after z-buffer
        float avgDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;
        projectedTriangle.avgDepth = avgDepth;

        trianglesToRender.push_back(projectedTriangle);
    }
    //TODO:remove after z-buffer
    std::sort(trianglesToRender.begin(), trianglesToRender.end(), [](const Triangle& t1, const Triangle& t2) {
        return t1.avgDepth > t2.avgDepth;
    });
}

void Renderer::Render() {
    DrawGrid();

    // Loop all projected triangles and render them
    for (auto& triangle: trianglesToRender) {
        // Draw filled triangle
        if (settings.renderMethod == RenderMethod::RENDER_FILL_TRIANGLE ||
            settings.renderMethod == RenderMethod::RENDER_FILL_TRIANGLE_WIRE) {
            graphics->FillTriangle(
                    triangle.points[0].x, triangle.points[0].y,
                    triangle.points[1].x, triangle.points[1].y,
                    triangle.points[2].x, triangle.points[2].y,
                    triangle.color
            );
        }

        // Draw textured triangle
        if (settings.renderMethod == RenderMethod::RENDER_TEXTURED ||
            settings.renderMethod == RenderMethod::RENDER_TEXTURED_WIRE) {
            graphics->DrawTexturedTriangle(
                    triangle.points[0].x, triangle.points[0].y,triangle.texcoords[0].u,triangle.texcoords[0].v,
                    triangle.points[1].x, triangle.points[1].y,triangle.texcoords[1].u,triangle.texcoords[1].v,
                    triangle.points[2].x, triangle.points[2].y,triangle.texcoords[2].u,triangle.texcoords[2].v,
                    mesh.texture
            );
        }

        // Draw triangle wireframe
        if (settings.renderMethod == RenderMethod::RENDER_WIRE ||
            settings.renderMethod == RenderMethod::RENDER_WIRE_VERTEX ||
            settings.renderMethod == RenderMethod::RENDER_FILL_TRIANGLE_WIRE ||
            settings.renderMethod == RenderMethod::RENDER_TEXTURED_WIRE) {
            graphics->DrawTriangle(
                    triangle.points[0].x, triangle.points[0].y,
                    triangle.points[1].x, triangle.points[1].y,
                    triangle.points[2].x, triangle.points[2].y,
                    triangle.color
            );
        }

        if (settings.renderMethod == RenderMethod::RENDER_WIRE_VERTEX) {
            graphics->DrawRect(triangle.points[0].x - 3, triangle.points[0].y, 6, 6, 0xFFFF0000);
            graphics->DrawRect(triangle.points[1].x - 3, triangle.points[1].y, 6, 6, 0xFFFF0000);
            graphics->DrawRect(triangle.points[2].x - 3, triangle.points[2].y, 6, 6, 0xFFFF0000);
        }
    }

    graphics->Render(renderer);
    gui->Render(settings);

    graphics->Clear(0xFF000000);
    trianglesToRender.clear();

    SDL_RenderPresent(renderer);
}

void Renderer::DrawGrid() {
    for (int x = 0; x < WINDOW_WIDTH; x += 10) {
        for (int y = 0; y < WINDOW_HEIGHT; y += 10) {
            graphics->DrawPixel(x, y, 0xFF444444);
        }
    }
}







