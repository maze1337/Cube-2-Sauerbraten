#include "Console.h"

void Console::Init()
{
    AllocConsole();
    SetConsoleTitleA("");

    freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);

    LOG("[+] Consoled Allocated!\n");
}

void Console::Shutdown()
{
    FreeConsole();
    fclose(stdin);
    fclose(stdout);
}
