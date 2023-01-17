#include "Renderer.h"


int main() {
    Renderer renderer{"../assets/f22.obj"};
    SDL_Event event;
    bool isRunning{true};

    auto ProcessInput = [&]() {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    isRunning = false;
                break;
        }
    };

    while (isRunning) {
        ProcessInput();
        renderer.Update();
        renderer.Render();
    }
    
    return 0;
}