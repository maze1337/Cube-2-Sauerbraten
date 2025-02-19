#include "Globals.h"


void Globals::Init()
{
    Globals::Base = (uintptr_t)GetModuleHandle("sauerbraten.exe");

    printf("[+] Globals Initiated!\n");
}

void Globals::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    Globals::Screen.x = io.DisplaySize.x;
    Globals::Screen.y = io.DisplaySize.y;

}