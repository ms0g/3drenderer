#include "App.h"


int main() {
    App app{};

    app.LoadMesh("../assets/f117.obj", "../assets/f117.png", {1, 1, 1}, {-3, 0, +8}, {0, 0, 0});
    app.LoadMesh("../assets/f22.obj", "../assets/f22.png", {1, 1, 1}, {3, 0, +8}, {0, 0, 0});

    while (app.IsRunning()) {
        app.Input();
        app.Update();
        app.Render();
    }
    return 0;
}