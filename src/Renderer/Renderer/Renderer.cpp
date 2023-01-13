#include "Renderer.h"
#include <iostream>

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
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    // Create texture
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT);

    cameraPos = {0, 0, -5};
    cubeRotation = {0, 0, 0};
    int point_count = 0;

    // Start loading my array of vectors
    // From -1 to 1 (in this 9x9x9 cube)
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                Vec3 new_point = {x, y, z};
                cube_points[point_count++] = new_point;
            }
        }
    }
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

    cubeRotation.x += 0.01;
    cubeRotation.y += 0.01;
    cubeRotation.z += 0.01  ;

    for (int i = 0; i < N_POINTS; i++) {
        Vec3 point = cube_points[i];

        Vec3 transformedPoint = point.Rotate(cubeRotation.x, cubeRotation.y, cubeRotation.z);

        // Move the point away from camera
        transformedPoint.z -= cameraPos.z;

        // Project the current point
        Vec2 projected_point = Project(transformedPoint);

        // Save the projected 2D vector in the array of projected points
        projected_points[i] = projected_point;
    }
}

void Renderer::Render() {
    DrawGrid();

    // Loop all projected points and render them
    for (auto projected_point: projected_points) {
        DrawRect(
                projected_point.x + (WINDOW_WIDTH / 2),
                projected_point.y + (WINDOW_HEIGHT / 2),
                4,
                4,
                0xFFFFFF00
        );
    }

    RenderColorBuffer();
    Clear(0xFF000000);

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

void Renderer::Clear(color_t color) {
    colorBuffer.fill(color);
}







