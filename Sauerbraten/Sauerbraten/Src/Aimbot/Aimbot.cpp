#include "Aimbot.h"

#define M_PI 3.14159265358979323846

Vector2 Aimbot::CalcAngle(Vector3 Src, Vector3 Dst)
{
    Vector2 Angle;

    Angle.x = static_cast<float>((atan2(Dst.x - Src.x, Dst.y - Src.y) * -1.0) / M_PI * 180.0);
    Angle.y = static_cast<float>(asinf((Dst.z - Src.z) / Src.Distance(Dst)) * (180.0 / M_PI));

    return Angle;
}

CEntity* Aimbot::GetClosestEnemy()
{
    CEntity* Target = nullptr;
    float ClosestDistance = FLT_MAX;

    const Vector2 screenCenter(Globals::Screen.x / 2, Globals::Screen.y / 2);

    for (int playerIndex = 0; playerIndex < GetPlayerCount(); playerIndex++)
    {
        CEntity* currentEntity = GetEntity(playerIndex);
        if (!currentEntity->IsValid()) continue;

        Vector2 headScreenPosition;
        if (!WorldToScreen(currentEntity->GetHead(), headScreenPosition)) continue;

        float CurrentDistance = screenCenter.Distance(headScreenPosition);

        if (CurrentDistance < ClosestDistance) 
        {
            ClosestDistance = CurrentDistance;
            Target = currentEntity;
        }
    }
    return Target;
}

void Aimbot::AimAt(CEntity* Entity)
{
    if (!Entity) return; 

    Vector2 Angle = CalcAngle(GetLocalPlayer()->GetHead(), Entity->GetHead());

    GetLocalPlayer()->Angles = Angle;
}
