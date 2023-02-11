#pragma once

enum class CullMethod {
    CULL_NONE,
    CULL_BACKFACE
};

enum class RenderMethod {
    RENDER_WIRE,
    RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE,
    RENDER_TEXTURED,
    RENDER_TEXTURED_WIRE
};

struct Settings {
    CullMethod cullMethod;
    RenderMethod renderMethod;
};
