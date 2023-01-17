#include "Renderer.h"
#include <iostream>
#include "ObjParser.h"
#include "MeshData.hpp"

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

    // Create texture
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT);

    cameraPos = {0, 0, -5};

    // Load Mesh data
    auto meshData = ObjParser::Load(objFile);
    mesh.SetData(meshData);
}


Renderer::~Renderer() {
    // Clean up SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    // Clean up texture
    SDL_DestroyTexture(texture);
}

void Renderer::Update() {
    auto timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(timeToWait);

    millisecsPreviousFrame = SDL_GetTicks();

    mesh.UpdateRotation(0.01);

    for (const auto& meshFace: mesh.GetFaces()) {
        Vec3 faceVertices[3];
        faceVertices[0] = mesh.GetVertices()[meshFace.a - 1];
        faceVertices[1] = mesh.GetVertices()[meshFace.b - 1];
        faceVertices[2] = mesh.GetVertices()[meshFace.c - 1];

        Triangle projectedTriangle;
        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; ++j) {
            Vec3 transformedVertex = faceVertices[j];

            transformedVertex = transformedVertex.Rotate(mesh.GetRotationX(), mesh.GetRotationY(), mesh.GetRotationZ());

            // Translate the vertex away from the camera
            transformedVertex.z -= cameraPos.z;

            // Project the current vertex
            Vec2 projectedPoint = Project(transformedVertex);

            // Scale and translate the projected points to the middle of the screen
            projectedPoint.x += (WINDOW_WIDTH / 2);
            projectedPoint.y += (WINDOW_HEIGHT / 2);

            projectedTriangle.points[j] = projectedPoint;

        }

        trianglesToRender.emplace_back(projectedTriangle);
    }
}

void Renderer::Render() {
    DrawGrid();

    // Loop all projected triangles and render them
    for (const auto& triangle: trianglesToRender) {
        // Draw vertex points
        DrawRect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
        DrawRect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
        DrawRect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

        // Draw unfilled triangles
        DrawTriangle(
                triangle.points[0].x,
                triangle.points[0].y,
                triangle.points[1].x,
                triangle.points[1].y,
                triangle.points[2].x,
                triangle.points[2].y,
                0xFF00FF00
        );
    }

    RenderColorBuffer();

    Clear(0xFF000000);
    trianglesToRender.clear();

    SDL_RenderPresent(renderer);
}

void Renderer::DrawGrid() {
    for (int x = 0; x < WINDOW_WIDTH; x += 10) {
        for (int y = 0; y < WINDOW_HEIGHT; y += 10) {
            PutPixel(x, y, 0xFF444444);
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

void Renderer::RenderColorBuffer() {
    SDL_UpdateTexture(texture,
                      nullptr,
                      colorBuffer.data(),
                      WINDOW_WIDTH * sizeof(color_t));

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Renderer::PutPixel(int x, int y, color_t color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        colorBuffer[(WINDOW_WIDTH * y) + x] = color;
}

void Renderer::DrawRect(int x, int y, int width, int height, color_t color) {
    for (int i = x; i <= (x + width); i++) {
        for (int j = y; j <= (y + height); j++) {
            PutPixel(i, j, color);
        }
    }
}

void Renderer::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    DDA(x0, y0, x1, y1, color);
    DDA(x1, y1, x2, y2, color);
    DDA(x2, y2, x0, y0, color);
}

void Renderer::DDA(int x0, int y0, int x1, int y1, color_t color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xinc = dx / static_cast<float>(step);
    float yinc = dy / static_cast<float>(step);

    float x = x0;
    float y = y0;

    for (int i = 0; i < step; ++i) {
        PutPixel(round(x), round(y), color);
        x += xinc;
        y += yinc;
    }
}

void Renderer::Clear(color_t color) {
    colorBuffer.fill(color);
}







