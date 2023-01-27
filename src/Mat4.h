#pragma once

class Vec4;
struct Mat4 {
    float m[4][4]{{0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}};

    static Mat4 IdentityMatrix();

    static Mat4 ScaleMatrix(float sx, float sy, float sz);

    static Mat4 TranslationMatrix(float tx, float ty, float tz);

    static Mat4 RotationZMatrix(float angle);

    static Mat4 RotationXMatrix(float angle);

    static Mat4 RotationYMatrix(float angle);

    Vec4 operator*(Vec4 v) const;
};


