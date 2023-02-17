#include "Graphics.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Texture.h"

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

void Graphics::DrawTexel(int x, int y, vec2 a, vec2 b, vec2 c,
                         float u0, float v0, float u1, float v1, float u2, float v2,
                         Texture* tex) {
    vec2 p = {static_cast<float>(x), static_cast<float>(y)};

    vec3 weights = utils::barycentric_weights(a, b, c, p);

    float alpha = weights.x;
    float beta = weights.y;
    float gamma = weights.z;

    // Perform the interpolation of all U and V values using barycentric weights
    float interpolated_U = u0 * alpha + u1 * beta + u2 * gamma;
    float interpolated_V = v0 * alpha + v1 * beta + v2 * gamma;

    // Map the UV coordinate to the full texture width and height
    int texX = abs(static_cast<int>(interpolated_U * (tex->width)));
    int texY = abs(static_cast<int>(interpolated_V * (tex->height)));

    DrawPixel(x, y, tex->data[texY * tex->width + texX]);
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
                                    Texture* tex) {
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

    // Create vector points
    vec2 a = {static_cast<float>(x0), static_cast<float>(y0)};
    vec2 b = {static_cast<float>(x1), static_cast<float>(y1)};
    vec2 c = {static_cast<float>(x2), static_cast<float>(y2)};

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
                DrawTexel(x, y, a, b, c, u0, v0, u1, v1, u2, v2, tex);
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
                DrawTexel(x, y, a, b, c, u0, v0, u1, v1, u2, v2, tex);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Return the barycentric weights alpha, beta, and gamma for point p
///////////////////////////////////////////////////////////////////////////////
//
//         (B)
//         /|\
//        / | \
//       /  |  \
//      /  (P)  \
//     /  /   \  \
//    / /       \ \
//   //           \\
//  (A)------------(C)
//
///////////////////////////////////////////////////////////////////////////////
vec3 utils::barycentric_weights(vec2 a, vec2 b, vec2 c, vec2 p) {
    vec2 ac = c - a;
    vec2 ab = b - a;
    vec2 ap = p - a;
    vec2 pc = c - p;
    vec2 pb = b - p;

    // Compute the area of the full parallegram/triangle ABC using 2D cross product
    float areaParallelogramABC = ac.Cross(ab);

    // Alpha is the area of the small parallelogram/triangle PBC divided by the area of the full parallelogram/triangle ABC
    float alpha = pc.Cross(pb) / areaParallelogramABC;

    // Beta is the area of the small parallelogram/triangle APC divided by the area of the full parallelogram/triangle ABC
    float beta = ac.Cross(ap) / areaParallelogramABC;

    // Weight gamma is easily found since barycentric coordinates always add up to 1.0
    float gamma = 1 - alpha - beta;

    return {alpha, beta, gamma};

}




