#include "Vec4.h"
#include "Vec3.h"

vec4::vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

void vec4::Add(const vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void vec4::Sub(const vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void vec4::Scale(float n) {
    x *= n;
    y *= n;
    z *= n;
    w *= n;
}

vec4 vec4::FromVec3(const vec3& v) {
    return {v.x, v.y, v.z, 1};
}

float vec4::Dot(const vec4& v) const {
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

vec4& vec4::operator=(const vec4& v) = default;

bool vec4::operator==(const vec4& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool vec4::operator!=(const vec4& v) const {
    return !(*this == v);
}

vec4 vec4::operator+(const vec4& v) const {
    vec4 result;
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    result.w = w + v.w;
    return result;
}

vec4 vec4::operator-(const vec4& v) const {
    vec4 result;
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    result.w = w - v.w;
    return result;
}

vec4 vec4::operator*(float n) const {
    vec4 result;
    result.x = x * n;
    result.y = y * n;
    result.z = z * n;
    result.w = w * n;
    return result;
}

vec4 vec4::operator/(float n) const {
    vec4 result;
    result.x = x / n;
    result.y = y / n;
    result.z = z / n;
    result.w = w / n;
    return result;
}

vec4& vec4::operator+=(const vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

vec4& vec4::operator-=(const vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

vec4& vec4::operator*=(float n) {
    x *= n;
    y *= n;
    z *= n;
    w *= n;
    return *this;
}

vec4& vec4::operator/=(float n) {
    x /= n;
    y /= n;
    z /= n;
    w /= n;
    return *this;
}

vec4 vec4::operator-() const {
    vec4 result;
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;
    result.w = w * -1;
    return result;
}

