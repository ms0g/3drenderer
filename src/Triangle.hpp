#pragma once

#include "Vec4.h"
#include "Texture.h"

struct TriangleFace {
    int a{}, b{}, c{};
    Texture a_uv, b_uv, c_uv;
    uint32_t color{};
};

struct Triangle {
    vec4 points[3];
    Texture texcoords[3];
    uint32_t color;
};
