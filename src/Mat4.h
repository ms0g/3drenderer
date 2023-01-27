#pragma once

class Vec4;
struct Mat4 {
    float m[4][4]{{0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}};

    static Mat4 IdentityMatrix();

    static Mat4 ScaleMatrix(float x, float y, float z);

    Vec4 operator*(Vec4 v) const;
};


