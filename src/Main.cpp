#include "Renderer.h"

int main() {
    Renderer renderer;
    renderer.Initialize();
    renderer.Run();
    renderer.Destroy();
    return 0;
}