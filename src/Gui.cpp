#include "Gui.h"
#include "Settings.hpp"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_sdl.h"
#include "../libs/imgui/imgui_impl_sdlrenderer.h"
#include "../libs/imgui/imgui_internal.h"

Gui::Gui(SDL_Window* window, SDL_Renderer* renderer) {
    // Initialize the ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
}

Gui::~Gui() {
    // Clean up ImGui
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::Render(Settings& settings) {
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

//    bool show_demo_window = true;
//    ImGui::ShowDemoWindow(&show_demo_window);

    if (ImGui::Begin("Render Settings")) {
        if (ImGui::Button("CB")) {
            settings.cullMethod = CULLMethod::CULL_BACKFACE;
        } else if (ImGui::Button("CN")) {
            settings.cullMethod = CULLMethod::CULL_NONE;
        } else if (ImGui::Button("RW")) {
            settings.renderMethod = RenderMethod::RENDER_WIRE;
        } else if (ImGui::Button("RWV")) {
            settings.renderMethod = RenderMethod::RENDER_WIRE_VERTEX;
        } else if (ImGui::Button("RFT")) {
            settings.renderMethod = RenderMethod::RENDER_FILL_TRIANGLE;
        } else if (ImGui::Button("RFTW")) {
            settings.renderMethod = RenderMethod::RENDER_FILL_TRIANGLE_WIRE;
        }
    }
    ImGui::End();


    //Render ImGui
    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}