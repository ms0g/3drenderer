#pragma once

class Settings;
class SDL_Window;
class SDL_Renderer;
class Gui {
public:
    Gui(SDL_Window* window, SDL_Renderer* renderer);

    ~Gui();

    void Render(Settings& settings);

    void UpdateFPSCounter(float dt);

private:
    double previousSeconds{};
    double currentSeconds{};
    int frameCount{};
    int fps;
};
