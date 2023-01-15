#pragma once

#include "Vec2.h"

struct TriangleFace {
    int a;
    int b;
    int c;
};

struct Triangle {
    Vec2 points[3];
};
