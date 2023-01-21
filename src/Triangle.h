#pragma once

#include "Vec2.h"
#include "Constants.hpp"

struct TriangleFace {
    int a;
    int b;
    int c;
};

class Graphics;
struct Triangle {
    Vec2 points[3];
    void FillWithColor(Graphics& graphics, color_t color);
private:

};
