#pragma once

#include <memory>
#include <vector>
#include "Mat4.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Graphics.h"
#include "Gui.h"
#include "Clipping.h"
#include "Constants.hpp"
#include "Settings.hpp"
#include "Triangle.hpp"


class App {
public:
    App(const char* objFile, const char* textureFile);

    [[nodiscard]] bool IsRunning() const;

    void Input();
    void Update();
    void Render();
private:
    bool isRunning;
    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<Gui> gui;

    std::vector<Triangle> trianglesToRender;

    mat4 projectionMatrix;

    Mesh mesh{};

    Frustum frustum{};

    Light light{0, 0, 1};

    Camera camera{};

    Settings settings{};

    float deltaTime{};
    uint32_t millisecsPreviousFrame{0};
    static constexpr int FPS = 60;
    static constexpr int MILLISECS_PER_FRAME = 1000 / FPS;

};
