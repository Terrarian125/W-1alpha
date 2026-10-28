#include "Gun.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
#include "Engine/Model.h"

using namespace DirectX;
using namespace std;

// コンストラクタ
Gun::Gun(GameObject* parent)
    :GameObject(parent, "Reticle"), position_{ 0.0f,0.0f,0.0f }, hModel_(-1)
{
}

// デストラクタ
Gun::~Gun()
{
}

// 初期化
void Gun::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("/Model/Gun00.fbx");
	assert(hModel_ >= 0);

    // 一応あると楽だからここに
    //transform_.position_ = { position_.x,position_.y,position_.z };  // 位置
    transform_.rotate_ = { -10.0f, 10.0f, 0.0f };  // 回転
    transform_.scale_  = { 0.5f,  0.5f, 0.5f }; // 拡大率


    //  (float)(rand() % 10 - 5)
    //位置
    // X - 1.2～1.2
    // Y 2.0～3.0
    // Z - 6.5～ - 8.0
    transform_.position_ = { -6.0f, -6.0f, 0 };  // 位置
}

// 更新
void Gun::Update()
{
}

// 描画
void Gun::Draw()
{
    // レティクル表示
    transform_.position_ = { position_.x,position_.y,position_.z };  // 位置
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

    // ImGui (デバック用)
    {
        // ======= レティクルの位置座標 =======
        ImGui::Begin("Gun_position");
        ImGui::InputFloat("pos.X", &position_.x);
        ImGui::InputFloat("pos.Y", &position_.y);
        ImGui::InputFloat("pos.Z", &position_.z);
        ImGui::End();
    }
}

void Gun::Release()
{
}

void Gun::Move()
{
}
