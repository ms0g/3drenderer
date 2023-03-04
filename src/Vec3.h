#pragma once


class vec4;
struct vec3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };

        float v[3];
    };

    vec3();

    vec3(float x, float y, float z);

    ~vec3() = default;

    void Add(const vec3& v);                            // v1.Add(v2)
    void Sub(const vec3& v);                            // v1.Sub(v2)
    void Scale(float n);                                // v1.Scale(n)
    [[nodiscard]] vec3 Rotate(float angleX,
                              float angleY,
                              float angleZ) const;      // v1.Rotate(angle)
    [[nodiscard]] vec3 RotateX(float angle) const;      // v1.RotateX(angle)
    [[nodiscard]] vec3 RotateY(float angle) const;      // v1.RotateY(angle)
    [[nodiscard]] vec3 RotateZ(float angle) const;      // v1.RotateZ(angle)

    [[nodiscard]] float Magnitude() const;              // v1.Magnitude()
    [[nodiscard]] float MagnitudeSquared() const;       // v1.MagnitudeSquared()

    vec3& Normalize();                                  // v1.Normalize()
    [[nodiscard]] vec3 UnitVector() const;              // v1.UnitVector()

    static vec3 FromVec4(const vec4& v);                // vec3::FromVec4(v4)

    [[nodiscard]] float Dot(const vec3& v) const;       // v1.Dot(v2)
    [[nodiscard]] vec3 Cross(const vec3& v) const;      // v1.Cross(v2)

    vec3& operator=(const vec3& v);                     // v1 = v2
    bool operator==(const vec3& v) const;               // v1 == v2
    bool operator!=(const vec3& v) const;               // v1 != v2

    vec3 operator+(const vec3& v) const;                // v1 + v2
    vec3 operator-(const vec3& v) const;                // v1 - v2
    vec3 operator*(float n) const;                      // v1 * n
    vec3 operator/(float n) const;                      // v1 / n
    vec3 operator-() const;                             // -v1

    vec3& operator+=(const vec3& v);                    // v1 += v2
    vec3& operator-=(const vec3& v);                    // v1 -= v2
    vec3& operator*=(float n);                          // v1 *= n
    vec3& operator/=(float n);                          // v1 /= n
};
