#pragma once

#include <cstdint>

struct texcoord {
    float u{}, v{};

    texcoord() = default;

    texcoord(float u, float v) : u(u), v(v) {}

    texcoord& operator=(const texcoord& other);
};

class upng_t;
class Texture {
public:
    explicit Texture(const char* filename);

    ~Texture();

    [[nodiscard]] int GetWidth() const;

    [[nodiscard]] int GetHeight() const;

    [[nodiscard]] uint32_t* GetData() const;

private:
    int width{}, height{};
    upng_t* upng{};
    uint32_t* data{};

};
