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


void vec2::Scale(float n) {
    x *= n;
    y *= n;
}


vec2 vec2::Rotate(float angle) const {
    return {x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)};
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
    vec2 result = {0, 0};
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
    return {x + v.x, y + v.y};
}


vec2 vec2::operator-(const vec2& v) const {
    return {x - v.x, y - v.y};
}


vec2 vec2::operator*(float n) const {
    return {x * n, y * n};
}


vec2 vec2::operator/(float n) const {
    return {x / n, y / n};
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


vec2& vec2::operator*=(float n) {
    x *= n;
    y *= n;
    return *this;
}


vec2& vec2::operator/=(float n) {
    x /= n;
    y /= n;
    return *this;
}


vec2 vec2::operator-() const {
    return {x * -1, y * -1};
}
