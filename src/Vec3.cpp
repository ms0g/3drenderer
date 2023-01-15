#include "Vec3.h"
#include <cmath>

Vec3::Vec3() : x(0.0), y(0.0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

void Vec3::Add(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vec3::Sub(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vec3::Scale(const float n) {
    x *= n;
    y *= n;
    z *= n;
}

Vec3 Vec3::Rotate(const float angleX, const float angleY, const float angleZ) const {
    Vec3 result = RotateX(angleX);
    result = result.RotateY(angleY);
    result = result.RotateZ(angleZ);
    return result;
}

Vec3 Vec3::RotateX(float angle) const {
    Vec3 result = {
        x,
        y * cos(angle) - z * sin(angle),
        y * sin(angle) + z * cos(angle)

    };
    return result;
}

Vec3 Vec3::RotateY(float angle) const {
    Vec3 result = {
            x * cos(angle) - z * sin(angle),
            y,
            x * sin(angle) + z * cos(angle)
    };
    return result;
}

Vec3 Vec3::RotateZ(float angle) const {
    Vec3 result = {
            x * cos(angle) - y * sin(angle),
            x * sin(angle) + y * cos(angle),
            z,
    };
    return result;
}

float Vec3::Magnitude() const {
    return sqrtf(x * x + y * y + z * z);
}

float Vec3::MagnitudeSquared() const {
    return (x * x + y * y + z * z);
}

Vec3& Vec3::Normalize() {
    float length = Magnitude();
    if (length != 0.0) {
        x /= length;
        y /= length;
        z /= length;
    }
    return *this;
}

Vec3 Vec3::UnitVector() const {
    Vec3 result = Vec3(0, 0, 0);
    float length = Magnitude();
    if (length != 0.0) {
        result.x = x / length;
        result.y = y / length;
        result.z = z / length;
    }
    return result;
}

//Vec3 Vec3::Normal() const {
//    return Vec3(y, -x, z).Normalize();
//}

float Vec3::Dot(const Vec3& v) const {
    return (x * v.x) + (y * v.y) + (z * v.z);
}

float Vec3::Cross(const Vec3& v) const {
    return (x * v.y) - (y * v.x);
}

Vec3& Vec3::operator=(const Vec3& v) = default;

bool Vec3::operator==(const Vec3& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool Vec3::operator!=(const Vec3& v) const {
    return !(*this == v);
}

Vec3 Vec3::operator+(const Vec3& v) const {
    Vec3 result;
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    return result;
}

Vec3 Vec3::operator-(const Vec3& v) const {
    Vec3 result;
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    return result;
}

Vec3 Vec3::operator*(const float n) const {
    Vec3 result;
    result.x = x * n;
    result.y = y * n;
    result.z = z * n;
    return result;
}

Vec3 Vec3::operator/(const float n) const {
    Vec3 result;
    result.x = x / n;
    result.y = y / n;
    result.z = z / n;
    return result;
}

Vec3& Vec3::operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3& Vec3::operator*=(const float n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

Vec3& Vec3::operator/=(const float n) {
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

Vec3 Vec3::operator-() const {
    Vec3 result;
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;
    return result;
}



