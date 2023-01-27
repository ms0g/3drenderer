#include "Vec4.h"
#include "Vec3.h"

Vec4::Vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

void Vec4::Add(const Vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void Vec4::Sub(const Vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void Vec4::Scale(float n) {
    x *= n;
    y *= n;
    z *= n;
    w *= n;
}

Vec4 Vec4::FromVec3(Vec3 v) {
    return {v.x, v.y, v.z, 1};
}

float Vec4::Dot(const Vec4& v) const {
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

Vec4& Vec4::operator=(const Vec4& v) = default;

bool Vec4::operator==(const Vec4& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vec4::operator!=(const Vec4& v) const {
    return !(*this == v);
}

Vec4 Vec4::operator+(const Vec4& v) const {
    Vec4 result;
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    result.w = w + v.w;
    return result;
}

Vec4 Vec4::operator-(const Vec4& v) const {
    Vec4 result;
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    result.w = w - v.w;
    return result;
}

Vec4 Vec4::operator*(float n) const {
    Vec4 result;
    result.x = x * n;
    result.y = y * n;
    result.z = z * n;
    result.w = w * n;
    return result;
}

Vec4 Vec4::operator/(float n) const {
    Vec4 result;
    result.x = x / n;
    result.y = y / n;
    result.z = z / n;
    result.w = w / n;
    return result;
}

Vec4& Vec4::operator+=(const Vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

Vec4& Vec4::operator-=(const Vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

Vec4& Vec4::operator*=(float n) {
    x *= n;
    y *= n;
    z *= n;
    w *= n;
    return *this;
}

Vec4& Vec4::operator/=(float n) {
    x /= n;
    y /= n;
    z /= n;
    w /= n;
    return *this;
}

Vec4 Vec4::operator-() const {
    Vec4 result;
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;
    result.w = w * -1;
    return result;
}

