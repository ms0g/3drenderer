#pragma once


struct Vec2 {
    float x;
    float y;

    Vec2();

    Vec2(float x, float y);

    ~Vec2() = default;

    void Add(const Vec2& v);                            // v1.Add(v2)
    void Sub(const Vec2& v);                            // v1.Sub(v2)
    void Scale(float n);                                // v1.Scale(n)
    [[nodiscard]] Vec2 Rotate(float angle) const;       // v1.Rotate(angle)

    [[nodiscard]] float Magnitude() const;              // v1.Magnitude()
    [[nodiscard]] float MagnitudeSquared() const;       // v1.MagnitudeSquared()

    Vec2& Normalize();                                  // v1.Normalize()
    [[nodiscard]] Vec2 UnitVector() const;              // v1.UnitVector()
    [[nodiscard]] Vec2 Normal() const;                  // n = v1.Normal()

    [[nodiscard]] float Dot(const Vec2& v) const;       // v1.Dot(v2)
    [[nodiscard]] float Cross(const Vec2& v) const;     // v1.Cross(v2)

    Vec2& operator=(const Vec2& v);                     // v1 = v2
    bool operator==(const Vec2& v) const;               // v1 == v2
    bool operator!=(const Vec2& v) const;               // v1 != v2

    Vec2 operator+(const Vec2& v) const;                // v1 + v2
    Vec2 operator-(const Vec2& v) const;                // v1 - v2
    Vec2 operator*(float n) const;                      // v1 * n
    Vec2 operator/(float n) const;                      // v1 / n
    Vec2 operator-() const;                             // -v1

    Vec2& operator+=(const Vec2& v);                    // v1 += v2
    Vec2& operator-=(const Vec2& v);                    // v1 -= v2
    Vec2& operator*=(float n);                          // v1 *= n
    Vec2& operator/=(float n);                          // v1 /= n
};