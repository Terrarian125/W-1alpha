#include "GuiButton.h"

#include <imgui.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <utility>

namespace
{
    //0xRRGGBBAA 形式の色を ImGui 用の色に変換する
    ImU32 ToImU32(unsigned int rgba)
    {
        const unsigned char r = static_cast<unsigned char>((rgba >> 24) & 0xFF);
        const unsigned char g = static_cast<unsigned char>((rgba >> 16) & 0xFF);
        const unsigned char b = static_cast<unsigned char>((rgba >> 8) & 0xFF);
        const unsigned char a = static_cast<unsigned char>(rgba & 0xFF);

        return IM_COL32(r, g, b, a);
    }

    ImVec2 ToImVec2(int x, int y)
    {
        return ImVec2(
            static_cast<float>(x),
            static_cast<float>(y)
        );
    }
}

GuiButton::GuiButton(
    int x,
    int y,
    int width,
    int height,
    std::string text
)
    : x(x),
    y(y),
    width(width),
    height(height),
    label(std::move(text))
{
}

void GuiButton::Draw()
{
    if (!active_ || width <= 0 || height <= 0)
    {
        return;
    }

    //ImGui が初期化されていなければ描画しない
    if (ImGui::GetCurrentContext() == nullptr)
    {
        return;
    }

    //ImGui::Begin("GuiButton Internal Debug");
    //ImGui::Text("Draw entered");
    //ImGui::Text("x=%d y=%d w=%d h=%d", x, y, width, height);
    //ImGui::End();

    //ボタンのインスタンスごとに異なるウィンドウ名を生成する
    char windowName[64];

    std::snprintf(
        windowName,
        sizeof(windowName),
        "##GuiButton_%p",
        static_cast<void*>(this)
    );

    ImGui::SetNextWindowPos(
        ToImVec2(x, y),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowSize(
        ToImVec2(width, height),
        ImGuiCond_Always
    );

    const ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoDocking;

    if (!ImGui::Begin(windowName, nullptr, flags))
    {
        ImGui::End();
        return;
    }
    //ImGui::Text("GuiButton is working!");

    ImGui::PushID(this);

    const ImVec2 buttonSize(
        static_cast<float>(width),
        static_cast<float>(height)
    );

    const ImVec2 buttonMin = ImGui::GetCursorScreenPos();
    const ImVec2 buttonMax(
        buttonMin.x + buttonSize.x,
        buttonMin.y + buttonSize.y
    );

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    const bool hovered =
        ImGui::IsMouseHoveringRect(buttonMin, buttonMax);

    const bool clicked =
        hovered &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left);

    //背景色
    unsigned int backgroundColor = normalColor_;

    if (hovered)
    {
        backgroundColor = hoveredColor_;
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && hovered)
    {
        backgroundColor = activeColor_;
    }

    //背景を描画
    drawList->AddRectFilled(
        buttonMin,
        buttonMax,
        ToImU32(backgroundColor)
    );

    //画像が設定されていれば画像を描画
    if (textureId_ != nullptr)
    {
        drawList->AddImage(
            static_cast<ImTextureID>(textureId_),
            buttonMin,
            buttonMax
        );
    }

    //ボタンの文字を描画
    if (!label.empty())
    {
        const ImVec2 textSize = ImGui::CalcTextSize(label.c_str());

        const ImVec2 textPos(
            buttonMin.x + (buttonSize.x - textSize.x) * 0.5f,
            buttonMin.y + (buttonSize.y - textSize.y) * 0.5f
        );

        drawList->AddText(
            textPos,
            ToImU32(textColor_),
            label.c_str()
        );
    }

    //説明文が設定されていればツールチップとして表示
    if (hovered && !description_.empty())
    {
        ImGui::SetTooltip("%s", description_.c_str());
    }

    //ImGui の入力処理領域を確保する
    ImGui::SetCursorScreenPos(buttonMin);

    ImGui::InvisibleButton(
        "##ButtonHitArea",
        buttonSize
    );

    //フォーカス枠
    if (focused_)
    {
        drawList->AddRect(
            buttonMin,
            buttonMax,
            IM_COL32(255, 220, 0, 255),
            0.0f,
            0,
            2.0f
        );
    }

    ImGui::PopID();
    ImGui::End();

    //コールバックはウィンドウを閉じた後に呼び出す
    if (clicked && onClick)
    {
        onClick();
    }
}

void GuiButton::SetPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

void GuiButton::SetSize(int newWidth, int newHeight)
{
    width = std::max(0, newWidth);
    height = std::max(0, newHeight);
}

void GuiButton::SetText(std::string text)
{
    label = std::move(text);
}

void GuiButton::SetFocus(bool focused)
{
    focused_ = focused;
}

bool GuiButton::IsFocused() const
{
    return focused_;
}

void GuiButton::SetActive(bool active)
{
    active_ = active;
}

bool GuiButton::IsActive() const
{
    return active_;
}

void GuiButton::SetDescription(std::string description)
{
    description_ = std::move(description);
}

const std::string& GuiButton::GetDescription() const
{
    return description_;
}

void GuiButton::SetImage(void* textureId)
{
    textureId_ = textureId;
}

void GuiButton::SetImageTint(unsigned int rgba)
{
    imageTint_ = rgba;
}

void GuiButton::ClearImage()
{
    textureId_ = nullptr;
}

void GuiButton::SetColors(
    unsigned int normal,
    unsigned int hovered,
    unsigned int active,
    unsigned int text
)
{
    normalColor_ = normal;
    hoveredColor_ = hovered;
    activeColor_ = active;
    textColor_ = text;
}

void GuiButton::SetTextColor(unsigned int rgba)
{
    textColor_ = rgba;
}