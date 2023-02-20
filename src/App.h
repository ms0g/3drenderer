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
#include "Triangle.h"


class App {
public:
    App();

    [[nodiscard]] bool IsRunning() const;

    void LoadMesh(const char* objFile, const char* textureFile, vec3 scale, vec3 translation, vec3 rotation);

    void Input();
    void Update();
    void Render();
private:
    void ProcessGraphicsPipeline(Mesh& mesh);

    bool isRunning;
    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<Gui> gui;

    std::vector<Triangle> trianglesToRender;
    std::vector<Mesh> meshes;

    mat4 projectionMatrix;

    Frustum frustum{};

    Light light{0, 0, 1};

    Camera camera{};

    Settings settings{};

    float deltaTime{};
    uint32_t millisecsPreviousFrame{0};
    static constexpr int FPS = 60;
    static constexpr int MILLISECS_PER_FRAME = 1000 / FPS;

};
