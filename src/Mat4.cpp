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

Mat4 Mat4::ScaleMatrix(float sx, float sy, float sz) {
    // | sx  0  0  0 |
    // |  0 sy  0  0 |
    // |  0  0 sz  0 |
    // |  0  0  0  1 |
    Mat4 _m = IdentityMatrix();

    _m.m[0][0] = sx;
    _m.m[1][1] = sy;
    _m.m[2][2] = sz;

    return _m;
}

Mat4 Mat4::TranslationMatrix(float tx, float ty, float tz) {
    // |  1  0  0  tx |
    // |  0  1  0  ty |
    // |  0  0  1  tz |
    // |  0  0  0  1  |
    Mat4 _m = IdentityMatrix();

    _m.m[0][3] = tx;
    _m.m[1][3] = ty;
    _m.m[2][3] = tz;

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

