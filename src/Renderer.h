#include <array>
#include <SDL2/SDL.h>
#include "Vec3.h"
#include "Vec2.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Constants.hpp"


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

    Vec3 cameraPos;
    Vec3 cubeRotation;

    SDL_Window* window{};
    SDL_Renderer* renderer{};

    SDL_Texture* texture{};
    std::array<color_t, WINDOW_WIDTH * WINDOW_HEIGHT> colorBuffer{};

    static constexpr int N_POINTS = (9 * 9 * 9);
    static constexpr float fov_factor = 640;

    Triangle trianglesToRender[N_MESH_FACES];

    uint32_t millisecsPreviousFrame{0};
    static constexpr int FPS = 60;
    static constexpr int MILLISECS_PER_FRAME = 1000 / FPS;




};

