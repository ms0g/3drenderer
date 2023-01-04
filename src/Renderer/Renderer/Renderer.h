#include <array>
#include <SDL2/SDL.h>
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Constants/Constants.hpp"


class Renderer {
public:
    Renderer();

    ~Renderer();

    void Update();

    void Render();

private:

    void DrawGrid();

    Vec2 Project(Vec3 point);

    void RenderColorBuffer();

    void PutPixel(int x, int y, color_t color);

    void DrawRect(int x, int y, int width, int height, color_t color);

    void Clear(color_t color);

    SDL_Window* window{};
    SDL_Renderer* renderer{};

    SDL_Texture* texture{};
    std::array<color_t, WINDOW_WIDTH * WINDOW_HEIGHT> colorBuffer{};

    static constexpr int N_POINTS = (9 * 9 * 9);
    static constexpr float fov_factor = 128;

    Vec3 cube_points[N_POINTS]; // 9x9x9 cube
    Vec2 projected_points[N_POINTS];



};

