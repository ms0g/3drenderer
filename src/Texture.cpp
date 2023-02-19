#include "Texture.h"
#include <iostream>
#include "../libs/upng/upng.h"


texcoord& texcoord::operator=(const texcoord& other) {
    if (this == &other) return *this;
    u = other.u;
    v = other.v;
    return *this;
}


Texture::Texture(const char* filename) {
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


Texture::~Texture() {
    upng_free(upng);
}


int Texture::GetWidth() const {
    return width;
}


int Texture::GetHeight() const {
    return height;
}


uint32_t* Texture::GetData() const {
    return data;
}
