#include "Texture.h"
#include <iostream>
#include "../libs/upng/upng.h"


Texture& Texture::operator=(const Texture& other) {
    if (this == &other) return *this;
    u = other.u;
    v = other.v;
    return *this;
}

PngTexture::PngTexture(const char* filename) {
    upng = upng_new_from_file(filename);
    if (upng != nullptr) {
        upng_decode(upng);
        if (upng_get_error(upng) == UPNG_EOK) {
            width = upng_get_width(upng);
            height = upng_get_height(upng);
            data = (uint32_t*) upng_get_buffer(upng);
        } else
            std::cerr << "Error decoding texture " << filename << "\n";
    } else {
        std::cerr << "Error loading texture " << filename << "\n";
    }
}

PngTexture::~PngTexture() {
    upng_free(upng);
}
