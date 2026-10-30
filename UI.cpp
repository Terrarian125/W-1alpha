#include "UI.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

// コンストラクタ
UI::UI(GameObject* parent)
    : GameObject(parent, "Reticle"), position_{ { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f } }, hImage_{ (-1), (-1) }
{
}

// デストラクタ
UI::~UI()
{
}

// 初期化
void UI::Initialize()
{
    // UIの画像のロード
    hImage_[0] = Image::Load("Image/Bullet.png"); // 弾
    assert(hImage_[0] >= 0);
    hImage_[1] = Image::Load("Image/Reticle.png"); // 無限マーク
    assert(hImage_[1] >= 0);

    // 一応あると楽だからここに
    position_[0] = { -0.92f, -0.75f, 0.0f }; // 位置
    rotate_[0]   = {   0.0f,   0.0f, 0.0f }; // 回転
    scale_[0]    = {   0.3f,   0.3f, 0.0f }; // 拡大率

    position_[1] = { -0.5f,  -0.25f, 0.0f }; // 位置
    rotate_[1]   = { 0.0f, 0.0f, 0.0f }; // 回転
    scale_[1]    = { 0.05f, 0.05f, 0.00f }; // 拡大率
}

// 更新
void UI::Update()
{
}

// 描画
void UI::Draw()
{
    // UI表示（弾）
    transform_.position_ = {position_[0].x,position_[0].y,position_[0].z};  // 位置
    transform_.scale_ = { scale_[0].x,scale_[0].y,scale_[0].z };  // 拡大率
    Image::SetTransform(hImage_[0], transform_);
    Image::Draw(hImage_[0]);

    // レティクル表示
    transform_.position_ = { position_[1].x,position_[1].y,position_[1].z };  // 位置
    transform_.scale_ = { scale_[1].x,scale_[1].y,scale_[1].z };  // 拡大率
    Image::SetTransform(hImage_[1], transform_);
    Image::Draw(hImage_[1]);

    // ImGui (デバック用)
    {
        // ======= UIの位置座標 =======
        ImGui::Begin("UI_position");
        ImGui::InputFloat("pos.X1", &position_[0].x);
        ImGui::InputFloat("pos.Y1", &position_[0].y);
        //ImGui::InputFloat("pos.Z1", &position_[0].z);
        ImGui::InputFloat("pos.X2", &position_[1].x);
        ImGui::InputFloat("pos.Y2", &position_[1].y);
        //ImGui::InputFloat("pos.Z2", &position_[1].z);
        ImGui::End();
    }
}

// 開放
void UI::Release()
{
}
