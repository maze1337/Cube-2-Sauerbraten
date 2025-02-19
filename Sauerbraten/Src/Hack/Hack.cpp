#include "Hack.h"
#include "../ESP/ESP.h"
#include "../Aimbot/Aimbot.h"


void Hack::Run()
{

    Globals::Update();

    if (GetAsyncKeyState(VK_XBUTTON2) && Gui::ESP)
    {
        Aimbot::AimAt(Aimbot::GetClosestEnemy());
    }
}

void Hack::Draw()
{
    if (!GetLocalPlayer() or !Gui::ESP) return;

    for (int i = 0; i < GetPlayerCount(); i++)
    {
        auto Entity = GetEntity(i);

        if (!Entity or !Entity->IsValid()) continue;

        Vector2 Bottom, Top;

        if (!WorldToScreen(Entity->GetPosition(), Bottom) or !WorldToScreen(Entity->GetHead() + Vector3(0.f, 0.f, 3.f), Top)) continue;

        ESP::Box(Bottom, Top);
        ESP::HealthBar(Bottom, Top, Entity->FPSState.Health);
        ESP::Name(Top, Entity->Name);
    }
}