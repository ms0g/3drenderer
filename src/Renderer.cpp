#include "Renderer.h"
#include <iostream>
#include "ObjParser.h"
#include "Graphics.h"
#include "Gui.h"
#include "MeshData.hpp"
#include "Vec4.h"
#include "Mat4.h"

Renderer::Renderer(const std::string& objFile) {
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
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    // Camera settings
    cameraPos = {0, 0, 0};

    // Load Mesh data
    auto meshData = ObjParser::Load(objFile);
    mesh.SetData(meshData);

    // Create color buffer
    graphics = std::make_unique<Graphics>(renderer);

    // Create Gui
    gui = std::make_unique<Gui>(window, renderer);

    // Render settings
    settings.cullMethod = CULLMethod::CULL_BACKFACE;
    settings.renderMethod = RenderMethod::RENDER_WIRE;
}


Renderer::~Renderer() {
    // Clean up SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Renderer::Update() {
    auto timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(timeToWait);

    millisecsPreviousFrame = SDL_GetTicks();

    mesh.UpdateRotation(0.01);

    //mesh.UpdateScaleX(0.002);

    mesh.UpdateTranslationX(0.01);
    // Translate the mesh away from the camera
    mesh.SetTranslationZ(5);

    // Create scale matrix that will be used to multiply the mesh vertices;
    Mat4 scaleMatrix = Mat4::ScaleMatrix(mesh.GetScaleX(), mesh.GetScaleY(), mesh.GetScaleZ());

    Mat4 translationMatrix = Mat4::TranslationMatrix(mesh.GetTranslationX(),
                                                     mesh.GetTranslationY(),
                                                     mesh.GetTranslationZ());

    Mat4 rotationXMatrix = Mat4::RotationXMatrix(mesh.GetRotationX());
    Mat4 rotationYMatrix = Mat4::RotationYMatrix(mesh.GetRotationY());
    Mat4 rotationZMatrix = Mat4::RotationZMatrix(mesh.GetRotationZ());


    for (const auto& meshFace: mesh.GetFaces()) {
        Vec3 faceVertices[3];
        faceVertices[0] = mesh.GetVertices()[meshFace.a - 1];
        faceVertices[1] = mesh.GetVertices()[meshFace.b - 1];
        faceVertices[2] = mesh.GetVertices()[meshFace.c - 1];

        Vec4 transformedVertices[3];
        // Loop all three vertices of this current face and apply transformations
        for (int i = 0; i < 3; ++i) {
            Vec4 transformedVertex = Vec4::FromVec3(faceVertices[i]);

            // Use a matrix to scale our original vertex
            transformedVertex = scaleMatrix * transformedVertex;
            transformedVertex = rotationXMatrix * transformedVertex;
            transformedVertex = rotationYMatrix * transformedVertex;
            transformedVertex = rotationZMatrix * transformedVertex;
            transformedVertex = translationMatrix * transformedVertex;

            transformedVertices[i] = transformedVertex;
        }

        // Check backface culling
        if (settings.cullMethod == CULLMethod::CULL_BACKFACE) {
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

            // Bypass the triangles that are looking away the camera
            if (dotNormalCamera < 0) {
                continue;
            }
        }

        Triangle projectedTriangle;
        // Loop all three vertices to perform projection
        for (int i = 0; i < 3; ++i) {
            // Project the current vertex
            Vec2 projectedPoint = Project(Vec3::FromVec4(transformedVertices[i]));

            // Scale and translate the projected points to the middle of the screen
            projectedPoint.x += (WINDOW_WIDTH / 2);
            projectedPoint.y += (WINDOW_HEIGHT / 2);

            projectedTriangle.points[i] = projectedPoint;
        }
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
        if (settings.renderMethod == RenderMethod::RENDER_FILL_TRIANGLE ||
            settings.renderMethod == RenderMethod::RENDER_FILL_TRIANGLE_WIRE) {
            graphics->FillTriangle(
                    triangle.points[0].x, triangle.points[0].y,
                    triangle.points[1].x, triangle.points[1].y,
                    triangle.points[2].x, triangle.points[2].y,
                    0xFF555555
            );
        }

        if (settings.renderMethod == RenderMethod::RENDER_WIRE ||
            settings.renderMethod == RenderMethod::RENDER_WIRE_VERTEX ||
            settings.renderMethod == RenderMethod::RENDER_FILL_TRIANGLE_WIRE) {
            graphics->DrawTriangle(
                    triangle.points[0].x, triangle.points[0].y,
                    triangle.points[1].x, triangle.points[1].y,
                    triangle.points[2].x, triangle.points[2].y,
                    0xFFFFFFFF
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

Vec2 Renderer::Project(Vec3 point) {
    Vec2 projected_point = {
            (fov_factor * point.x) / point.z,
            (fov_factor * point.y) / point.z
    };

    return projected_point;
}







