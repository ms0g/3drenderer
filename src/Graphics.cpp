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


//////////////////////////////////////////////////////////////////////////////
// Draw a filled triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//          (x0,y0)
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   (x1,y1)------(Mx,My)
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         (x2,y2)
//
///////////////////////////////////////////////////////////////////////////////
void Graphics::FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }

    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    if (y1 == y2) {
        // Draw flat-bottom triangle
        FillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // Draw flat-top triangle
        FillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        FillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        FillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
    }
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
    // Inverse slope because we're calculating the x changes with respect to y
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

//////////////////////////////////////////////////////////////////////////////
// Draw a textured triangle with the flat-top/flat-bottom method
// We split the original triangle in two, half flat-bottom and half flat-top
///////////////////////////////////////////////////////////////////////////////
//
//           u0,v0
//            / \
//           /   \
//          /     \
//         /       \
//        /         \
//   u1,v1-----------\
//       \_           \
//          \_         \
//             \_       \
//                \_     \
//                   \    \
//                     \_  \
//                        \_\
//                           \
//                         u2, v2
//
///////////////////////////////////////////////////////////////////////////////
void Graphics::DrawTexturedTriangle(int x0, int y0, float u0, float v0,
                                    int x1, int y1, float u1, float v1,
                                    int x2, int y2, float u2, float v2,
                                    uint32_t* tex) {
    // We need to sort vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
        std::swap(u0, u1);
        std::swap(v0, v1);
    }

    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
        std::swap(u1, u2);
        std::swap(v1, v2);
    }

    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
        std::swap(u0, u1);
        std::swap(v0, v1);
    }

     /////////////////////////////////////////////////////////
     // Render the upper part of the triangle (flat-bottom) //
     ////////////////////////////////////////////////////// //

    float invSlope1 = (y1 - y0) != 0 ? static_cast<float>(x1 - x0) / abs(y1 - y0) : 0;
    float invSlope2 = (y2 - y0) != 0 ? static_cast<float>(x2 - x0) / abs(y2 - y0) : 0;

    if (y1 - y0 != 0) {
        for (int y = y0; y <= y1; ++y) {
            int xStart = x1 + (y - y1) * invSlope1;
            int xEnd = x0 + (y - y0) * invSlope2;

            if (xEnd < xStart)
                std::swap(xStart, xEnd);

            for (int x = xStart; x < xEnd; ++x) {
                DrawPixel(x, y, 0xFFFFF00FF);
            }
        }
    }

    ////////////////////////////////////////////////////////
    // Render the bottom part of the triangle (flat-top)  //
    ////////////////////////////////////////////////////////
    invSlope1 = (y2 - y1) != 0 ? static_cast<float>(x2 - x1) / abs(y2 - y1) : 0;
    invSlope2 = (y2 - y0) != 0 ? static_cast<float>(x2 - x0) / abs(y2 - y0) : 0;

    if (y2 - y1 != 0) {
        for (int y = y1; y <= y2; ++y) {
            int xStart = x1 + (y - y1) * invSlope1;
            int xEnd = x0 + (y - y0) * invSlope2;

            if (xEnd < xStart)
                std::swap(xStart, xEnd);

            for (int x = xStart; x < xEnd; ++x) {
                DrawPixel(x, y, 0xFFFFF00FF);
            }
        }
    }
}




