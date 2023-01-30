#pragma once

#include <cstdint>
#include <numbers>

constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};

constexpr float fov{std::numbers::pi/3.0};
constexpr float aspect{(float)WINDOW_HEIGHT/(float)WINDOW_WIDTH};
constexpr float znear{0.1};
constexpr float zfar{100.0};

using color_t = uint32_t;
