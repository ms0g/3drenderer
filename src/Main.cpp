#include "App.h"


int main() {
    App app{};

    app.LoadMesh("../assets/runway.obj", "../assets/runway.png", {1, 1, 1}, {0, -1.5, +23}, {0, 0, 0});
    app.LoadMesh("../assets/f22.obj", "../assets/f22.png", {1, 1, 1}, {0, -1.3, +5}, {0, -M_PI/2, 0});
    app.LoadMesh("../assets/efa.obj", "../assets/efa.png", {1, 1, 1}, {-2, -1.3, +9}, {0, -M_PI/2, 0});
    app.LoadMesh("../assets/f117.obj", "../assets/f117.png", {1, 1, 1}, {+2, -1.3, +9}, {0, -M_PI/2, 0});

    while (app.IsRunning()) {
        app.Input();
        app.Update();
        app.Render();
    }
    return 0;
}