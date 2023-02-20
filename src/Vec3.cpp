#include "Vec3.h"
#include <cmath>
#include "Vec4.h"

vec3::vec3() : x(0.0), y(0.0), z(0.0) {}

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

void vec3::Add(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}


void vec3::Sub(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}


void vec3::Scale(float n) {
    x *= n;
    y *= n;
    z *= n;
}


vec3 vec3::Rotate(float angleX, float angleY, float angleZ) const {
    vec3 result = RotateX(angleX);
    result = result.RotateY(angleY);
    result = result.RotateZ(angleZ);
    return result;
}


vec3 vec3::RotateX(float angle) const {
    return {x,
            y * cos(angle) - z * sin(angle),
            y * sin(angle) + z * cos(angle)
    };
}


vec3 vec3::RotateY(float angle) const {
    return {x * cos(angle) - z * sin(angle),
            y,
            x * sin(angle) + z * cos(angle)
    };
}


vec3 vec3::RotateZ(float angle) const {
    return {x * cos(angle) - y * sin(angle),
            x * sin(angle) + y * cos(angle),
            z};
}


float vec3::Magnitude() const {
    return sqrtf(x * x + y * y + z * z);
}


float vec3::MagnitudeSquared() const {
    return (x * x + y * y + z * z);
}


vec3& vec3::Normalize() {
    float length = Magnitude();
    if (length != 0.0) {
        x /= length;
        y /= length;
        z /= length;
    }
    return *this;
}


vec3 vec3::UnitVector() const {
    vec3 result = vec3(0, 0, 0);
    float length = Magnitude();
    if (length != 0.0) {
        result.x = x / length;
        result.y = y / length;
        result.z = z / length;
    }
    return result;
}


vec3 vec3::FromVec4(const vec4& v) {
    return {v.x, v.y, v.z};
}


float vec3::Dot(const vec3& v) const {
    return (x * v.x) + (y * v.y) + (z * v.z);
}


vec3 vec3::Cross(const vec3& v) const {
    return {y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x};
}


vec3& vec3::operator=(const vec3& v) = default;

bool vec3::operator==(const vec3& v) const {
    return x == v.x && y == v.y && z == v.z;
}


bool vec3::operator!=(const vec3& v) const {
    return !(*this == v);
}


vec3 vec3::operator+(const vec3& v) const {
    return {x + v.x,
            y + v.y,
            z + v.z};
}


vec3 vec3::operator-(const vec3& v) const {
    return {x - v.x,
            y - v.y,
            z - v.z};
}


vec3 vec3::operator*(float n) const {
    return {x * n, y * n, z * n};
}


vec3 vec3::operator/(float n) const {
    return {x / n, y / n, z / n};
}


vec3& vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}


vec3& vec3::operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}


vec3& vec3::operator*=(float n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}


vec3& vec3::operator/=(float n) {
    x /= n;
    y /= n;
    z /= n;
    return *this;
}


vec3 vec3::operator-() const {
    return {x * -1, y * -1, z * -1};
}



