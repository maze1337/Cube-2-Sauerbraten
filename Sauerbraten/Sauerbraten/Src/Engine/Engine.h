#pragma once
#include "../Includes/Includes.h"

// Offsets
#define OFFSET_LOCALPLAYER  0x2A5730
#define OFFSET_ENTITYLIST   0x346C90
#define OFFSET_ENTITYSIZE   0x346C9C
#define OFFSET_CLIENTLIST   0x3472E0 // Bots
#define OFFSET_VIEWMATRIX   0x32D040


//Useful fuction ptrs
#define DRAW_TEXT 0x15F2B0
#define PRINT_TO_CONSOLE 0x1B5350

class CEntity;
class CFPSState;


CEntity* GetLocalPlayer();
int GetPlayerCount();
CEntity* GetEntity(int index);
bool WorldToScreen(Vector3 pos, Vector2& screen);

class CFPSState
{
public:
    uint32_t Health;         // 0x0000
    uint32_t MaxHealth;      // 0x0004
    uint32_t Armour;         // 0x0008
    uint32_t ArmourType;     // 0x000C
    uint32_t QuadMillis;     // 0x0010
    uint32_t SelectedGun;    // 0x0014
    uint32_t GunWait;        // 0x0018
    uint32_t Ammo[12];       // 0x001C
    uint32_t AIType;         // 0x004C
    uint32_t Skill;          // 0x0050
}; 


class CEntity
{
public:
    Vector3 Head; //0x0000
    Vector3 Velocity; //0x000C
    char pad_0018[36]; //0x0018
    Vector2 Angles; //0x003C
    char pad_0044[8]; //0x0044
    float Radius; //0x004C
    char pad_0050[292]; //0x0050
    uint8_t Occluded; //0x0174
    char pad_0175[3]; //0x0175
    CFPSState FPSState; //0x0178
    char pad_01CC[48]; //0x01CC
    bool Shoot; //0x01FC
    char pad_01FD[119]; //0x01FD
    char Name[16]; //0x0274
    char pad_0284[244]; //0x0284
    uint8_t Team; //0x0378

    Vector3 GetPosition()
    {
        return this->Head + Vector3(0.f, 0.f, -15.f);
    }

    Vector3 GetHead()
    {
        return this->Head;
    }

    bool IsValid()
    {
        if (this == nullptr)
            return false;

        if (this->Head.x == 0.f && this->Head.y == 0.f && this->Head.z == 0.f)
            return false; // Not a spectator

        if (this->Angles.x == 0.f && this->Angles.y == 0.f)
            return false; // Not a spectator

        if (this->FPSState.Health < 1 || this->FPSState.Health > this->FPSState.MaxHealth)
            return false; // Is alive

        if (GetLocalPlayer()->Team == this->Team)
            return false; // Is enemy

        return true;
    }

    void SetAmmo(int Ammo)
    {
        auto Weapon = this->FPSState.SelectedGun;
        this->FPSState.Ammo[Weapon] = Ammo;
    }
};