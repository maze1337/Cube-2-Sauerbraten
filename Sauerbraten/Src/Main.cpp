#include "Includes/Includes.h"
#include "Console/Console.h"
#include "Hooks/Hooks.h"
#include "Hack/Hack.h"


DWORD WINAPI Main(LPVOID Param)
{
    Console::Init();
    Globals::Init();
    Hooks::Init();

    while (!GetAsyncKeyState(VK_END))
    {
        Hack::Run();
    }

    Console::Shutdown();
    Hooks::Shutdown();

    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(Param), 0);
}

BOOL APIENTRY DllMain(HMODULE Instance, DWORD Reason, LPVOID Reserved)
{
    if (Reason == DLL_PROCESS_ATTACH)
    {
        const auto Thread = CreateThread(0, 0, Main, Instance, 0, 0);

        if (Thread)
            CloseHandle(Thread);
    }
    return TRUE;
}