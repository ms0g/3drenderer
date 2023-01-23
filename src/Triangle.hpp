#pragma once

#include "Vec2.h"

struct TriangleFace {
    int a, b, c;
};

struct Triangle {
    Vec2 points[3];
    float avgDepth;
};
