#include <array>
#include <SDL2/SDL.h>
#include <vector>
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

    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

    void DDA(int x0, int y0, int x1, int y1, color_t color);

    void Clear(color_t color);

    Mesh<N_CUBE_VERTICES, N_CUBE_FACES> mesh{cubeVertices, cubeFaces, {0, 0, 0}};

    Vec3 cameraPos;

    SDL_Window* window{};
    SDL_Renderer* renderer{};

    SDL_Texture* texture{};
    std::array<color_t, WINDOW_WIDTH * WINDOW_HEIGHT> colorBuffer{};

    static constexpr int N_POINTS = (9 * 9 * 9);
    static constexpr float fov_factor = 640;

    std::vector<Triangle> trianglesToRender;

    uint32_t millisecsPreviousFrame{0};
    static constexpr int FPS = 60;
    static constexpr int MILLISECS_PER_FRAME = 1000 / FPS;


};

