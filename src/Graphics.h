#pragma once

#include <array>
#include <SDL2/SDL.h>
#include "Constants.hpp"

class Graphics {
public:
    explicit Graphics(SDL_Renderer* renderer);

    ~Graphics();

    void Clear(color_t color);

    void Render(SDL_Renderer* renderer);

    void DrawRect(int x, int y, int width, int height, color_t color);

    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void DrawTexturedTriangle(int x0, int y0, float u0, float v0,
                              int x1, int y1, float u1, float v1,
                              int x2, int y2, float u2, float v2,
                              uint32_t* tex);

    void DDA(int x0, int y0, int x1, int y1, color_t color);

    void DrawPixel(int x, int y, color_t color);

    void FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

private:
    SDL_Texture* texture{};
    std::array<color_t, WINDOW_WIDTH * WINDOW_HEIGHT> colorBuffer{};

};
