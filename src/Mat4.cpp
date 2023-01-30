#include <cmath>
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

Mat4 Mat4::PerspectiveMatrix(float fov, float aspect, float znear, float zfar) {
    // | (h/w)*1/tan(fov/2)             0              0                 0 |
    // |                  0  1/tan(fov/2)              0                 0 |
    // |                  0             0     zf/(zf-zn)  (-zf*zn)/(zf-zn) |
    // |                  0             0              1                 0 |
    Mat4 _m;
    _m.m[0][0] = aspect * (1/ tan(fov/2));
    _m.m[1][1] = 1 / tan(fov/2);
    _m.m[2][2] = zfar / (zfar-znear);
    _m.m[2][3] = (-zfar * znear)/(zfar-znear);
    _m.m[3][2] = 1.0;

    return _m;

}

Mat4 Mat4::RotationZMatrix(float angle) {
    // | c -s  0  0 |
    // | s  c  0  0 |
    // | 0  0  1  0 |
    // | 0  0  0  1 |
    Mat4 _m = IdentityMatrix();

    _m.m[0][0] = cos(angle);
    _m.m[0][1] = -sin(angle);
    _m.m[1][0] = sin(angle);
    _m.m[1][1] = cos(angle);

    return _m;
}

Mat4 Mat4::RotationXMatrix(float angle) {
    // | 1  0  0  0 |
    // | 0  c -s  0 |
    // | 0  s  c  0 |
    // | 0  0  0  1 |
    Mat4 _m = IdentityMatrix();

    _m.m[1][1] = cos(angle);
    _m.m[1][2] = -sin(angle);
    _m.m[2][1] = sin(angle);
    _m.m[2][2] = cos(angle);

    return _m;
}

Mat4 Mat4::RotationYMatrix(float angle) {
    // |  c  0  s  0 |
    // |  0  1  0  0 |
    // | -s  0  c  0 |
    // |  0  0  0  1 |
    Mat4 _m = IdentityMatrix();

    _m.m[0][0] = cos(angle);
    _m.m[0][2] = sin(angle);
    _m.m[2][0] = -sin(angle);
    _m.m[2][2] = cos(angle);

    return _m;
}

Vec4 Mat4::operator*(Vec4 v) const {
    Vec4 _v{};

    _v.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    _v.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    _v.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    _v.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

    return _v;
}

Mat4 Mat4::operator*(Mat4 m1) const {
    Mat4 _m;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            _m.m[i][j] = m[i][0] * m1.m[0][j] + m[i][1] * m1.m[1][j] + m[i][2] * m1.m[2][j] + m[i][3] * m1.m[3][j];
        }
    }

    return _m;
}

