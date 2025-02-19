#include "Gui.h"

void Gui::Init(HWND hwnd)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init();

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 5, io.DisplaySize.y / 5), ImGuiCond_FirstUseEver); // Set position (X:100, Y:100)
}

void Gui::Menu(bool &ShowMenu)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2 - 50, io.DisplaySize.y / 2 - 50), ImGuiCond_FirstUseEver); // Set position (X:100, Y:100)

    ImGui::Begin("Menu", &ShowMenu, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Checkbox("ESP", &Gui::ESP);
    ImGui::Checkbox("Aimbot", &Gui::Aimbot);
    ImGui::Checkbox("Silent Aim", &Gui::SilentAim);
    ImGui::End();
}
