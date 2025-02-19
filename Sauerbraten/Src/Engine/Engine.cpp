#include "Engine.h"

CEntity* GetLocalPlayer()
{
	return *(CEntity**)(Globals::Base + OFFSET_LOCALPLAYER);
}

int GetPlayerCount()
{
	return *(int*)(Globals::Base + OFFSET_ENTITYSIZE);
}

CEntity* GetEntity(int index) //Returns pointer to obj by "fpsent"
{
	auto EntityList = *(uintptr_t*)(Globals::Base + OFFSET_ENTITYLIST);

	return *(CEntity**)(EntityList + index * 0x8);
}

bool WorldToScreen(Vector3 pos, Vector2& screen)
{
	float* Matrix = (float*)(Globals::Base + OFFSET_VIEWMATRIX);

	Vector4 clipCoords;
	clipCoords.x = pos.x * Matrix[0] + pos.y * Matrix[4] + pos.z * Matrix[8] + Matrix[12];
	clipCoords.y = pos.x * Matrix[1] + pos.y * Matrix[5] + pos.z * Matrix[9] + Matrix[13];
	clipCoords.z = pos.x * Matrix[2] + pos.y * Matrix[6] + pos.z * Matrix[10] + Matrix[14];
	clipCoords.w = pos.x * Matrix[3] + pos.y * Matrix[7] + pos.z * Matrix[11] + Matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	screen.x = (Globals::Screen.x / 2 * NDC.x) + (NDC.x + Globals::Screen.x / 2);
	screen.y = -(Globals::Screen.y / 2 * NDC.y) + (NDC.y + Globals::Screen.y / 2);
	return true;
}