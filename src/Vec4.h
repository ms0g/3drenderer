#pragma once

class vec3;
struct vec4 {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };

        float v[4];
    };

    vec4();

    vec4(float x, float y, float z, float w);

    void Add(const vec4& v);                            // v1.Add(v2)
    void Sub(const vec4& v);                            // v1.Sub(v2)
    void Scale(float n);                                // v1.Scale(n)

    [[nodiscard]] float Dot(const vec4& v) const;       // v1.Dot(v2)

    static vec4 FromVec3(const vec3& v);                // vec4::FromVec3(v3)

    vec4& operator=(const vec4& v);                     // v1 = v2
    bool operator==(const vec4& v) const;               // v1 == v2
    bool operator!=(const vec4& v) const;               // v1 != v2

    vec4 operator+(const vec4& v) const;                // v1 + v2
    vec4 operator-(const vec4& v) const;                // v1 - v2
    vec4 operator*(float n) const;                      // v1 * n
    vec4 operator/(float n) const;                      // v1 / n
    vec4 operator-() const;                             // -v1

    vec4& operator+=(const vec4& v);                    // v1 += v2
    vec4& operator-=(const vec4& v);                    // v1 -= v2
    vec4& operator*=(float n);                          // v1 *= n
    vec4& operator/=(float n);                          // v1 /= n
};
