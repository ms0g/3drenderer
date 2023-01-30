#include <array>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"
#include "Mat4.h"
#include "Mesh.h"
#include "Triangle.hpp"
#include "Constants.hpp"
#include "Settings.hpp"


class Graphics;
class Gui;
class Renderer {
public:
    explicit Renderer(const std::string& objFile);

    ~Renderer();

    void Update();

    void Render();

private:
    void DrawGrid();

    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<Gui> gui;

    Mesh mesh{};

    Vec3 cameraPos;

    Mat4 projectionMatrix;

    SDL_Window* window{};
    SDL_Renderer* renderer{};

    Settings settings{};

    std::vector<Triangle> trianglesToRender;

    uint32_t millisecsPreviousFrame{0};
    static constexpr int FPS = 60;
    static constexpr int MILLISECS_PER_FRAME = 1000 / FPS;
};

