#pragma once

#include "Vec2.h"
#include "Texture.h"

struct TriangleFace {
    int a{}, b{}, c{};
    Texture a_uv, b_uv, c_uv;
    uint32_t color{};
};

struct Triangle {
    Vec2 points[3];
    Texture texcoords[3];
    float avgDepth;
    uint32_t color;
};
