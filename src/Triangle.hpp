#pragma once

#include "Vec2.h"

struct TriangleFace {
    int a, b, c;
    uint32_t color;
};

struct Triangle {
    Vec2 points[3];
    float avgDepth;
    uint32_t color;
};
