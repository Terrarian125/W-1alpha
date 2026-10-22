#pragma once

#include <imgui.h>

class MyCursor
{
public:
    MyCursor() = default;

    //カーソル画像を設定する
    void SetTexture(ImTextureID texture);

    //表示サイズを設定する
    void SetSize(float width, float height);

    //画像内のクリック基準点を設定する
    void SetHotspot(float x, float y);

    //表示・非表示を設定する
    void SetVisible(bool visible);

    //カーソルを描画する
    void Draw() const;

private:
    ImTextureID texture_ = nullptr;

    ImVec2 size_ = ImVec2(32.0f, 32.0f);
    ImVec2 hotspot_ = ImVec2(0.0f, 0.0f);

    bool visible_ = true;
};