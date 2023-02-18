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

void vec3::Scale(const float n) {
    x *= n;
    y *= n;
    z *= n;
}

vec3 vec3::Rotate(const float angleX, const float angleY, const float angleZ) const {
    vec3 result = RotateX(angleX);
    result = result.RotateY(angleY);
    result = result.RotateZ(angleZ);
    return result;
}

vec3 vec3::RotateX(float angle) const {
    vec3 result = {
            x,
            y * cos(angle) - z * sin(angle),
            y * sin(angle) + z * cos(angle)

    };
    return result;
}

vec3 vec3::RotateY(float angle) const {
    vec3 result = {
            x * cos(angle) - z * sin(angle),
            y,
            x * sin(angle) + z * cos(angle)
    };
    return result;
}

vec3 vec3::RotateZ(float angle) const {
    vec3 result = {
            x * cos(angle) - y * sin(angle),
            x * sin(angle) + y * cos(angle),
            z,
    };
    return result;
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
    vec3 result;
    result.x = y * v.z - z * v.y;
    result.y = z * v.x - x * v.z;
    result.z = x * v.y - y * v.x;
    return result;
}

vec3& vec3::operator=(const vec3& v) = default;

bool vec3::operator==(const vec3& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool vec3::operator!=(const vec3& v) const {
    return !(*this == v);
}

vec3 vec3::operator+(const vec3& v) const {
    vec3 result;
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    return result;
}

vec3 vec3::operator-(const vec3& v) const {
    vec3 result;
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    return result;
}

vec3 vec3::operator*(const float n) const {
    vec3 result;
    result.x = x * n;
    result.y = y * n;
    result.z = z * n;
    return result;
}

vec3 vec3::operator/(const float n) const {
    vec3 result;
    result.x = x / n;
    result.y = y / n;
    result.z = z / n;
    return result;
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

vec3& vec3::operator*=(const float n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

vec3& vec3::operator/=(const float n) {
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

vec3 vec3::operator-() const {
    vec3 result;
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;
    return result;
}



