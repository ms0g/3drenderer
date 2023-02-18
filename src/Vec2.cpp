#include "Vec2.h"
#include <cmath>
#include "Vec4.h"


vec2::vec2() : x(0.0), y(0.0) {}

vec2::vec2(float x, float y) : x(x), y(y) {}

void vec2::Add(const vec2& v) {
    x += v.x;
    y += v.y;
}

void vec2::Sub(const vec2& v) {
    x -= v.x;
    y -= v.y;
}

void vec2::Scale(const float n) {
    x *= n;
    y *= n;
}

vec2 vec2::Rotate(const float angle) const {
    vec2 result;
    result.x = x * cos(angle) - y * sin(angle);
    result.y = x * sin(angle) + y * cos(angle);
    return result;
}

float vec2::Magnitude() const {
    return sqrtf(x * x + y * y);
}

float vec2::MagnitudeSquared() const {
    return (x * x + y * y);
}

vec2& vec2::Normalize() {
    float length = Magnitude();
    if (length != 0.0) {
        x /= length;
        y /= length;
    }
    return *this;
}

vec2 vec2::UnitVector() const {
    vec2 result = vec2(0, 0);
    float length = Magnitude();
    if (length != 0.0) {
        result.x = x / length;
        result.y = y / length;
    }
    return result;
}

vec2 vec2::Normal() const {
    return vec2(y, -x).Normalize();
}

float vec2::Dot(const vec2& v) const {
    return (x * v.x) + (y * v.y);
}

float vec2::Cross(const vec2& v) const {
    return x * v.y - y * v.x;
}

vec2 vec2::FromVec4(const vec4& v) {
    return {v.x, v.y};
}

vec2& vec2::operator=(const vec2& v) = default;

bool vec2::operator==(const vec2& v) const {
    return x == v.x && y == v.y;
}

bool vec2::operator!=(const vec2& v) const {
    return !(*this == v);
}

vec2 vec2::operator+(const vec2& v) const {
    vec2 result;
    result.x = x + v.x;
    result.y = y + v.y;
    return result;
}

vec2 vec2::operator-(const vec2& v) const {
    vec2 result;
    result.x = x - v.x;
    result.y = y - v.y;
    return result;
}

vec2 vec2::operator*(const float n) const {
    vec2 result;
    result.x = x * n;
    result.y = y * n;
    return result;
}

vec2 vec2::operator/(const float n) const {
    vec2 result;
    result.x = x / n;
    result.y = y / n;
    return result;
}

vec2& vec2::operator+=(const vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

vec2& vec2::operator-=(const vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2& vec2::operator*=(const float n) {
    x *= n;
    y *= n;
    return *this;
}

vec2& vec2::operator/=(const float n) {
    x /= n;
    y /= n;
    return *this;
}

vec2 vec2::operator-() const {
    vec2 result;
    result.x = x * -1;
    result.y = y * -1;
    return result;
}
