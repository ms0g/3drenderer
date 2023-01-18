#pragma once


struct Vec3 {
    float x, y, z;

    Vec3();

    Vec3(float x, float y, float z);

    ~Vec3() = default;

    void Add(const Vec3& v);                            // v1.Add(v2)
    void Sub(const Vec3& v);                            // v1.Sub(v2)
    void Scale(float n);                                // v1.Scale(n)
    [[nodiscard]] Vec3 Rotate(float angleX,
                              float angleY,
                              float angleZ) const;      // v1.Rotate(angle)
    [[nodiscard]] Vec3 RotateX(float angle) const;      // v1.RotateX(angle)
    [[nodiscard]] Vec3 RotateY(float angle) const;      // v1.RotateY(angle)
    [[nodiscard]] Vec3 RotateZ(float angle) const;      // v1.RotateZ(angle)

    [[nodiscard]] float Magnitude() const;              // v1.Magnitude()
    [[nodiscard]] float MagnitudeSquared() const;       // v1.MagnitudeSquared()

    Vec3& Normalize();                                  // v1.Normalize()
    [[nodiscard]] Vec3 UnitVector() const;              // v1.UnitVector()
    [[nodiscard]] Vec3 Normal() const;                  // n = v1.Normal()

    [[nodiscard]] float Dot(const Vec3& v) const;       // v1.Dot(v2)
    [[nodiscard]] Vec3 Cross(const Vec3& v) const;      // v1.Cross(v2)

    Vec3& operator=(const Vec3& v);                     // v1 = v2
    bool operator==(const Vec3& v) const;               // v1 == v2
    bool operator!=(const Vec3& v) const;               // v1 != v2

    Vec3 operator+(const Vec3& v) const;                // v1 + v2
    Vec3 operator-(const Vec3& v) const;                // v1 - v2
    Vec3 operator*(float n) const;                      // v1 * n
    Vec3 operator/(float n) const;                      // v1 / n
    Vec3 operator-() const;                             // -v1

    Vec3& operator+=(const Vec3& v);                    // v1 += v2
    Vec3& operator-=(const Vec3& v);                    // v1 -= v2
    Vec3& operator*=(float n);                          // v1 *= n
    Vec3& operator/=(float n);                          // v1 /= n
};
