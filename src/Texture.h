#pragma once

#include <cstdint>


struct Texture {
    float u{}, v{};
    int width{}, height{};

    Texture() : width(64),height(64) {}
    Texture(float u, float v);

    Texture& operator=(const Texture& other);
};

extern const uint8_t REDBRICK_TEXTURE[];
