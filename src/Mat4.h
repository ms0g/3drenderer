#pragma once

class vec3;
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

    static mat4 RotationMatrixZ(float angle);

    static mat4 RotationMatrixX(float angle);

    static mat4 RotationMatrixY(float angle);

    static mat4 LookAt(vec3 eye, vec3 target, vec3 up);

    vec4 operator*(vec4 v) const;

    mat4 operator*(mat4 v) const;
};


