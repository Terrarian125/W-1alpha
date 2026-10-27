#include "MyCursor.h"
#include <imgui.h>

void MyCursor::SetTexture(ImTextureID texture)
{
    texture_ = texture;
}

void MyCursor::SetSize(float width, float height)
{
    size_.x = (width > 0.0f) ? width : 1.0f;
    size_.y = (height > 0.0f) ? height : 1.0f;
}

void MyCursor::SetHotspot(float x, float y)
{
    hotspot_.x = x;
    hotspot_.y = y;
}

void MyCursor::SetVisible(bool visible)
{
    visible_ = visible;
}

void MyCursor::Draw() const
{
    if (!visible_ || texture_ == nullptr)
        return;

    if (ImGui::GetCurrentContext() == nullptr)
        return;

    //ImGui が取得したマウス位置
    const ImVec2 mousePos = ImGui::GetIO().MousePos;

    if (mousePos.x < 0.0f || mousePos.y < 0.0f)
        return;

    //ホットスポットを考慮した描画位置
    const ImVec2 imageMin(
        mousePos.x - hotspot_.x,
        mousePos.y - hotspot_.y
    );

    const ImVec2 imageMax(
        imageMin.x + size_.x,
        imageMin.y + size_.y
    );

    //全UIの前面に描画
    ImGui::GetForegroundDrawList()->AddImage(
        texture_,
        imageMin,
        imageMax
    );
}