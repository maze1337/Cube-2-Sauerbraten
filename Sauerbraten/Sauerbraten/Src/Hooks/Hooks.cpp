#include "Hooks.h"

#include "../Hack/Hack.h"
#include "../Aimbot/Aimbot.h"


bool ShowMenu = true;
HWND hwnd = nullptr;
WNDPROC oWndProc = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef int(*SDL_SetRelativeMouseMode_t)(int);
inline auto DetourSDL_RelativeMouseMode = reinterpret_cast<SDL_SetRelativeMouseMode_t>(GetProcAddress(GetModuleHandle("SDL2.dll"), "SDL_SetRelativeMouseMode"));

LRESULT WINAPI hkWndProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDrawCursor = ShowMenu;

    DetourSDL_RelativeMouseMode(!ShowMenu); // Free mouse from the center

    // Allow ImGui to handle input if the menu is open
    if (ShowMenu)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, umsg, wParam, lParam))
            return true; // Block input from reaching the game

        //DetourSDL_RelativeMouseMode(0); // Free mouse from the center


        // Block the game from handling mouse movement when menu is open
        if (umsg == WM_MOUSEMOVE || umsg == WM_LBUTTONDOWN || umsg == WM_RBUTTONDOWN)
            return 0; // Prevent the game from processing mouse input
    }

    // Call the original window procedure for all other inputs
    return CallWindowProcW(oWndProc, hWnd, umsg, wParam, lParam);
}

typedef BOOL(WINAPI* tSwapBuffers)(HDC);
tSwapBuffers oSwapBuffers = nullptr;

BOOL WINAPI hkSwapBuffers(HDC hdc)
{
    static bool initialized = false;
    if (!initialized)
    {
        hwnd = WindowFromDC(hdc);

        Gui::Init(hwnd);

        oWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)hkWndProc);

        initialized = true;
    }

    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        ShowMenu = !ShowMenu;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Hack::Draw();
    
    if (ShowMenu)
    {
        Gui::Menu(ShowMenu);
    }

 
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return oSwapBuffers(hdc);
}

typedef void(__fastcall* tShoot)(CEntity* Player, Vector3* Target);
inline tShoot oShoot;

void __fastcall hkShoot(CEntity* Player, Vector3* Target)
{
    if (Gui::SilentAim)
    {
        if (Player == GetLocalPlayer())
        {
            CEntity* target = Aimbot::GetClosestEnemy();

            if (target)
            {
                *Target = target->GetHead();
            }
        }
    }

    oShoot(Player, Target);
}


void Hooks::Init()
{
    MH_Initialize();

    void* pSwapBuffers = reinterpret_cast<void*>(GetProcAddress(GetModuleHandleA("gdi32.dll"), "SwapBuffers"));
   
    MH_CreateHook(pSwapBuffers, &hkSwapBuffers, reinterpret_cast<LPVOID*>(&oSwapBuffers));
    MH_EnableHook(pSwapBuffers);

    void* pShoot = reinterpret_cast<void*>(Globals::Base + 0x1DB4C0);

    MH_CreateHook(pShoot, &hkShoot, (LPVOID*)&oShoot);
    MH_EnableHook(pShoot);


    printf("[+] SwapBuffers successfully hooked!\n");
}

void Hooks::Shutdown()
{
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)oWndProc);

    // Disable hooks before uninjecting
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);

    // Shutdown ImGui properly
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // Uninitialize MinHook
    MH_Uninitialize();
}


