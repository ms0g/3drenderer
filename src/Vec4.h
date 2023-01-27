#pragma once

class Vec3;
struct Vec4 {
    float x, y, z, w;

    Vec4();

    Vec4(float x, float y, float z, float w);

    void Add(const Vec4& v);                            // v1.Add(v2)
    void Sub(const Vec4& v);                            // v1.Sub(v2)
    void Scale(float n);                                // v1.Scale(n)

    [[nodiscard]] float Dot(const Vec4& v) const;       // v1.Dot(v2)

    static Vec4 FromVec3(Vec3 v);

    Vec4& operator=(const Vec4& v);                     // v1 = v2
    bool operator==(const Vec4& v) const;               // v1 == v2
    bool operator!=(const Vec4& v) const;               // v1 != v2

    Vec4 operator+(const Vec4& v) const;                // v1 + v2
    Vec4 operator-(const Vec4& v) const;                // v1 - v2
    Vec4 operator*(float n) const;                      // v1 * n
    Vec4 operator/(float n) const;                      // v1 / n
    Vec4 operator-() const;                             // -v1

    Vec4& operator+=(const Vec4& v);                    // v1 += v2
    Vec4& operator-=(const Vec4& v);                    // v1 -= v2
    Vec4& operator*=(float n);                          // v1 *= n
    Vec4& operator/=(float n);                          // v1 /= n
};
