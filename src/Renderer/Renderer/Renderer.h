#include <array>
#include <SDL2/SDL.h>
#include "Constants/Constants.hpp"


class Renderer {
public:
    Renderer();

    ~Renderer();

    void Update();

    void Render();

private:
    void Initialize();

    void Setup();

    void RenderColorBuffer();

    void PutPixel(int x, int y, color_t color);

    void DrawRect(int x, int y, int width, int height, color_t color);

    void Clear(color_t color);

    SDL_Window* window{};
    SDL_Renderer* renderer{};

    SDL_Texture* texture{};
    std::array<color_t, WINDOW_WIDTH * WINDOW_HEIGHT> colorBuffer{};

};

