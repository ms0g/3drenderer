#include "Mat4.h"
#include "Vec4.h"

Mat4 Mat4::IdentityMatrix() {
    return {{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
}

Mat4 Mat4::ScaleMatrix(float x, float y, float z) {
    // | sx  0  0  0 |
    // |  0 sy  0  0 |
    // |  0  0 sz  0 |
    // |  0  0  0  1 |
    Mat4 _m = IdentityMatrix();

    _m.m[0][0] = x;
    _m.m[1][1] = y;
    _m.m[2][2] = z;

    return _m;
}

Vec4 Mat4::operator*(Vec4 v) const {
    Vec4 result{};

    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

    return result;
}

