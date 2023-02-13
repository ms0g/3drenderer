#pragma once


struct vec2 {
    float x, y;

    vec2();

    vec2(float x, float y);

    ~vec2() = default;

    void Add(const vec2& v);                            // v1.Add(v2)
    void Sub(const vec2& v);                            // v1.Sub(v2)
    void Scale(float n);                                // v1.Scale(n)
    [[nodiscard]] vec2 Rotate(float angle) const;       // v1.Rotate(angle)

    [[nodiscard]] float Magnitude() const;              // v1.Magnitude()
    [[nodiscard]] float MagnitudeSquared() const;       // v1.MagnitudeSquared()

    vec2& Normalize();                                  // v1.Normalize()
    [[nodiscard]] vec2 UnitVector() const;              // v1.UnitVector()
    [[nodiscard]] vec2 Normal() const;                  // n = v1.Normal()

    [[nodiscard]] float Dot(const vec2& v) const;       // v1.Dot(v2)

    vec2& operator=(const vec2& v);                     // v1 = v2
    bool operator==(const vec2& v) const;               // v1 == v2
    bool operator!=(const vec2& v) const;               // v1 != v2

    vec2 operator+(const vec2& v) const;                // v1 + v2
    vec2 operator-(const vec2& v) const;                // v1 - v2
    vec2 operator*(float n) const;                      // v1 * n
    vec2 operator/(float n) const;                      // v1 / n
    vec2 operator-() const;                             // -v1

    vec2& operator+=(const vec2& v);                    // v1 += v2
    vec2& operator-=(const vec2& v);                    // v1 -= v2
    vec2& operator*=(float n);                          // v1 *= n
    vec2& operator/=(float n);                          // v1 /= n
};