#include "Graphics.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Texture.h"
#include "Vec4.h"

Graphics::Graphics(SDL_Renderer* renderer) {
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA32,
                                SDL_TEXTUREACCESS_STREAMING,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT);
}


Graphics::~Graphics() {
    SDL_DestroyTexture(texture);
}


void Graphics::Clear(color_t color) {
    colorBuffer.fill(color);
}


void Graphics::ClearDepthBuffer() {
    depthBuffer.fill(1.0);
}


void Graphics::Render(SDL_Renderer* renderer) {
    SDL_UpdateTexture(texture,
                      nullptr,
                      colorBuffer.data(),
                      WINDOW_WIDTH * sizeof(color_t));

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
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
void Graphics::DrawTexturedTriangle(int x0, int y0, float z0, float w0, Texture& aTex,
                                    int x1, int y1, float z1, float w1, Texture& bTex,
                                    int x2, int y2, float z2, float w2, Texture& cTex,
                                    const PngTexture& tex) {
    // We need to sort vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
        std::swap(z0, z1);
        std::swap(w0, w1);
        std::swap(aTex.u, bTex.u);
        std::swap(aTex.v, bTex.v);
    }

    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
        std::swap(z1, z2);
        std::swap(w1, w2);
        std::swap(bTex.u, cTex.u);
        std::swap(bTex.v, cTex.v);
    }

    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
        std::swap(z0, z1);
        std::swap(w0, w1);
        std::swap(aTex.u, bTex.u);
        std::swap(aTex.v, bTex.v);
    }

    // Flip the V values to account the inverted UV-coordinates (V grows downwards)
    aTex.v = 1 - aTex.v;
    bTex.v = 1 - bTex.v;
    cTex.v = 1 - cTex.v;

    // Create vector points
    vec4 a = {static_cast<float>(x0), static_cast<float>(y0), z0, w0};
    vec4 b = {static_cast<float>(x1), static_cast<float>(y1), z1, w1};
    vec4 c = {static_cast<float>(x2), static_cast<float>(y2), z2, w2};

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
                DrawTexel(x, y, a, b, c, aTex, bTex, cTex, tex);
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
                DrawTexel(x, y, a, b, c, aTex, bTex, cTex, tex);
            }
        }
    }
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
//   (x1,y1)---------\
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
void Graphics::DrawFilledTriangle(int x0, int y0, float z0, float w0,
                                  int x1, int y1, float z1, float w1,
                                  int x2, int y2, float z2, float w2,
                                  color_t color) {
    // We need to sort vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
        std::swap(z0, z1);
        std::swap(w0, w1);
    }

    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
        std::swap(z1, z2);
        std::swap(w1, w2);
    }

    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
        std::swap(z0, z1);
        std::swap(w0, w1);
    }

    // Create vector points
    vec4 a = {static_cast<float>(x0), static_cast<float>(y0), z0, w0};
    vec4 b = {static_cast<float>(x1), static_cast<float>(y1), z1, w1};
    vec4 c = {static_cast<float>(x2), static_cast<float>(y2), z2, w2};

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
                DrawTrixel(x, y, a, b, c, color);
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
                DrawTrixel(x, y, a, b, c, color);
            }
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


void Graphics::DrawRect(int x, int y, int width, int height, color_t color) {
    for (int i = x; i <= (x + width); i++) {
        for (int j = y; j <= (y + height); j++) {
            DrawPixel(i, j, color);
        }
    }
}


void Graphics::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    DDA(x0, y0, x1, y1, color);
    DDA(x1, y1, x2, y2, color);
    DDA(x2, y2, x0, y0, color);
}


void Graphics::DrawPixel(int x, int y, color_t color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        colorBuffer[(WINDOW_WIDTH * y) + x] = color;
}


void Graphics::DrawTexel(int x, int y, vec4 a, vec4 b, vec4 c,
                         Texture& aTex, Texture& bTex, Texture& cTex,
                         const PngTexture& tex) {
    vec2 p = {static_cast<float>(x), static_cast<float>(y)};

    vec2 av2 = vec2::FromVec4(a);
    vec2 bv2 = vec2::FromVec4(b);
    vec2 cv2 = vec2::FromVec4(c);

    vec3 weights = utils::barycentric_weights(av2, bv2, cv2, p);

    float alpha = weights.x;
    float beta = weights.y;
    float gamma = weights.z;

    // variables to store the interpolated values of u,v and reciprocal w (1/w) for the current pixel
    float interpolated_U;
    float interpolated_V;
    float interpolated_R_W;

    // Perform the interpolation of all U/w and V/w values using barycentric weights and a factor of 1/w
    interpolated_U = (aTex.u / a.w) * alpha + (bTex.u / b.w) * beta + (cTex.u / c.w) * gamma;
    interpolated_V = (aTex.v / a.w) * alpha + (bTex.v / b.w) * beta + (cTex.v / c.w) * gamma;
    interpolated_R_W = (1 / a.w) * alpha + (1 / b.w) * beta + (1 / c.w) * gamma;

    // Divide back the interpolated values by 1/w
    interpolated_U /= interpolated_R_W;
    interpolated_V /= interpolated_R_W;

    // Map the UV coordinate to the full texture width and height
    int texX = abs(static_cast<int>(interpolated_U * tex.width)) % tex.width;
    int texY = abs(static_cast<int>(interpolated_V * tex.height)) % tex.height;

    // Adjust 1/w so the pixels that are closer to the camera have smaller values
    interpolated_R_W = 1.0 - interpolated_R_W;

    if (interpolated_R_W < depthBuffer[(WINDOW_WIDTH * y) + x]) {
        DrawPixel(x, y, tex.data[texY * tex.width + texX]);
        depthBuffer[(WINDOW_WIDTH * y) + x] = interpolated_R_W;
    }
}


void Graphics::DrawTrixel(int x, int y, vec4 a, vec4 b, vec4 c, color_t color) {
    vec2 p = {static_cast<float>(x), static_cast<float>(y)};

    vec2 av2 = vec2::FromVec4(a);
    vec2 bv2 = vec2::FromVec4(b);
    vec2 cv2 = vec2::FromVec4(c);

    vec3 weights = utils::barycentric_weights(av2, bv2, cv2, p);

    float alpha = weights.x;
    float beta = weights.y;
    float gamma = weights.z;

    float interpolated_R_W = (1 / a.w) * alpha + (1 / b.w) * beta + (1 / c.w) * gamma;

    interpolated_R_W = 1.0 - interpolated_R_W;

    if (interpolated_R_W < depthBuffer[(WINDOW_WIDTH * y) + x]) {
        DrawPixel(x, y, color);
        depthBuffer[(WINDOW_WIDTH * y) + x] = interpolated_R_W;
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




