#pragma once

#include <cstdint>

struct Texture {
    float u{}, v{};

    Texture() = default;

    Texture(float u, float v): u(u), v(v) {}

    Texture& operator=(const Texture& other);
};

class upng_t;
struct PngTexture {
    int width{}, height{};
    upng_t* upng{};
    uint32_t* data{};

    explicit PngTexture(const char* filename);

    ~PngTexture();
};
