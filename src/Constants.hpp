#pragma once

#include <cstdint>
#include <numbers>

constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};

constexpr float ASPECT_Y{(float) WINDOW_HEIGHT / (float) WINDOW_WIDTH};
constexpr float ASPECT_X{(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT};

constexpr float FOV_Y{std::numbers::pi / 3.0};
const float FOV_X{2 * atan(tan(FOV_Y / 2) * ASPECT_X)};

constexpr float ZNEAR{1.0};
constexpr float ZFAR{20.0};

using color_t = uint32_t;
