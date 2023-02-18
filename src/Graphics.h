#pragma once

#include <array>
#include <SDL2/SDL.h>
#include "Constants.hpp"

class vec2;
class vec3;
class vec4;
class Texture;
class PngTexture;

namespace utils {
vec3 barycentric_weights(vec2 a, vec2 b, vec2 c, vec2 p);
}

class Graphics {
public:
    explicit Graphics(SDL_Renderer* renderer);

    ~Graphics();

    void Clear(color_t color);

    void Render(SDL_Renderer* renderer);

    void DrawRect(int x, int y, int width, int height, color_t color);

    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void DrawTexturedTriangle(int x0, int y0, float z0, float w0, Texture& aTex,
                              int x1, int y1, float z1, float w1, Texture& bTex,
                              int x2, int y2, float z2, float w2, Texture& cTex,
                              PngTexture* tex);

    void DDA(int x0, int y0, int x1, int y1, color_t color);

    void DrawPixel(int x, int y, color_t color);

    void DrawTexel(int x, int y, vec4 a, vec4 b, vec4 c, Texture& aTex, Texture& bTex, Texture& cTex, PngTexture* tex);

    void FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

private:
    SDL_Texture* texture{};
    std::array<color_t, WINDOW_WIDTH * WINDOW_HEIGHT> colorBuffer{};

};
