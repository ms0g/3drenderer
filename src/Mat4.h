#pragma once

class vec4;
struct mat4 {
    float m[4][4]{{0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}};

    static mat4 IdentityMatrix();

    static mat4 ScaleMatrix(float sx, float sy, float sz);

    static mat4 TranslationMatrix(float tx, float ty, float tz);

    static mat4 PerspectiveMatrix(float fov, float aspect, float znear, float zfar);

    static mat4 RotationZMatrix(float angle);

    static mat4 RotationXMatrix(float angle);

    static mat4 RotationYMatrix(float angle);

    vec4 operator*(vec4 v) const;

    mat4 operator*(mat4 v) const;
};


