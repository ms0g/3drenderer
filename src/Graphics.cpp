#include "Graphics.h"

Graphics::Graphics(SDL_Renderer* renderer) {
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT);
}

Graphics::~Graphics() {
    SDL_DestroyTexture(texture);
}

void Graphics::Render(SDL_Renderer* renderer) {
    SDL_UpdateTexture(texture,
                      nullptr,
                      colorBuffer.data(),
                      WINDOW_WIDTH * sizeof(color_t));

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Graphics::DrawPixel(int x, int y, color_t color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        colorBuffer[(WINDOW_WIDTH * y) + x] = color;
}

void Graphics::Clear(color_t color) {
    colorBuffer.fill(color);
}

void Graphics::DrawRect(int x, int y, int width, int height, color_t color) {
    for (int i = x; i <= (x + width); i++) {
        for (int j = y; j <= (y + height); j++) {
            DrawPixel(i, j, color);
        }
    }
}

void Graphics::DDA(int x0, int y0, int x1, int y1, color_t color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xinc = dx / static_cast<float>(step);
    float yinc = dy / static_cast<float>(step);

    float x = x0;
    float y = y0;

    for (int i = 0; i < step; ++i) {
        DrawPixel(round(x), round(y), color);
        x += xinc;
        y += yinc;
    }
}

void Graphics::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    DDA(x0, y0, x1, y1, color);
    DDA(x1, y1, x2, y2, color);
    DDA(x2, y2, x0, y0, color);
}


///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat bottom
///////////////////////////////////////////////////////////////////////////////
//
//        (x0,y0)
//          / \
//         /   \
//        /     \
//       /       \
//      /         \
//  (x1,y1)------(x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Graphics::FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    float invSlope1 = (static_cast<float>(x1 - x0)) / (y1 - y0);
    float invSlope2 = (static_cast<float>(x2 - x0)) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x0;
    float xEnd = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; ++y) {
        DDA(xStart, y, xEnd, y, color);
        xStart += invSlope1;
        xEnd += invSlope2;

    }
}


///////////////////////////////////////////////////////////////////////////////
// Draw a filled a triangle with a flat top
///////////////////////////////////////////////////////////////////////////////
//
//  (x0,y0)------(x1,y1)
//      \         /
//       \       /
//        \     /
//         \   /
//          \ /
//        (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Graphics::FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    float invSlope1 = (static_cast<float>(x2 - x0)) / (y2 - y0);
    float invSlope2 = (static_cast<float>(x2 - x1)) / (y2 - y1);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x2;
    float xEnd = x2;

    // Loop all the scanlines from top to bottom
    for (int y = y2; y >= y0; --y) {
        DDA(xStart, y, xEnd, y, color);
        xStart -= invSlope1;
        xEnd -= invSlope2;

    }
}




