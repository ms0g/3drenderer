#include "Renderer.h"
#include "../libs/imgui/imgui_impl_sdl.h"


int main() {
    Renderer renderer{};
    SDL_Event event;
    bool isRunning{true};

    auto ProcessInput = [&]() {
        SDL_PollEvent(&event);

        ImGui_ImplSDL2_ProcessEvent(&event);
        ImGuiIO& io = ImGui::GetIO();

        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.MousePos = ImVec2(mouseX, mouseY);
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

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

    renderer.LoadMesh("../assets/crab.obj");
    renderer.LoadTexture("../assets/crab.png");

    while (isRunning) {
        ProcessInput();
        renderer.Update();
        renderer.Render();
    }
    
    return 0;
}