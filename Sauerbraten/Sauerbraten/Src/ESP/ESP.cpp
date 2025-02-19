#include "ESP.h"

void ESP::Box(Vector2 Bottom, Vector2 Top)
{
    const float Height = Bottom.y - Top.y;
    const float Width = Height * 0.5f;  

    const ImVec2 TopLeft(Top.x - Width / 2, Top.y);
    const ImVec2 BottomRight(Top.x + Width / 2, Bottom.y);

    ImGui::GetBackgroundDrawList()->AddRect(TopLeft, BottomRight, ImColor(255,255,255));
}

void ESP::HealthBar(Vector2 Bottom, Vector2 Top, int Health)
{
    const float Height = Bottom.y - Top.y;
    const float Width = Height * 0.5f;

    const float HealthFrac = Health * 0.01f;
    const float HealthBarWidth = 2.0f; 

    const float BarX = Top.x + (Width / 2) + 1;

    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(BarX, Bottom.y - (Height * HealthFrac)),ImVec2(BarX + HealthBarWidth, Bottom.y),ImColor(ImVec4((1.f - HealthFrac), HealthFrac, 0, 1.0f)) );
}

void ESP::Name(Vector2 Top, std::string Name)
{
    ImVec2 textSize = ImGui::CalcTextSize(Name.c_str()); 
    ImVec2 textPos(Top.x - textSize.x / 2, Top.y - textSize.y - 2);

    ImGui::GetBackgroundDrawList()->AddText(textPos, ImColor(255, 255, 255, 255), Name.c_str());
}
