#include "Light.h"

Light::Light(float x, float y, float z) {
    direction.x = x;
    direction.y = y;
    direction.z = z;

}

Light::Light(vec3 direction) : direction(direction) {}

uint32_t Light::ApplyLightIntensity(uint32_t color, float factor) {
    if (factor < 0) factor = 0;
    if (factor > 1) factor = 1;
    uint32_t a = color & 0xFF000000;
    uint32_t r = (color & 0x00FF0000) * factor;
    uint32_t g = (color & 0x0000FF00) * factor;
    uint32_t b = (color & 0x000000FF) * factor;

    return (a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF));
}
