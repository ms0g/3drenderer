#pragma once

#include <cstdint>
#include <numbers>

constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};

constexpr float FOV{std::numbers::pi / 3.0};
constexpr float ASPECT{(float)WINDOW_HEIGHT / (float)WINDOW_WIDTH};
constexpr float ZNEAR{0.1};
constexpr float ZFAR{100.0};

using color_t = uint32_t;
