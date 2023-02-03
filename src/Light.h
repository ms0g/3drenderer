#pragma once

#include <cstdint>
#include "Vec3.h"

struct Light {
    Vec3 direction;

    Light(float x, float y, float z);

    explicit Light(Vec3 direction);

    static uint32_t ApplyLightIntensity(uint32_t color, float factor);
};



