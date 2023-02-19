#include "App.h"


int main() {
    App app{"../assets/crab.obj", "../assets/crab.png"};

    while (app.IsRunning()) {
        app.Input();
        app.Update();
        app.Render();
    }
    
    return 0;
}