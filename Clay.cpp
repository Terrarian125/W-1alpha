#include "Clay.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
using namespace DirectX;

//コンストラクタ
Clay::Clay(GameObject* parent)
    :GameObject(parent, "Clay"), hModel_{ (-1,-1,-1) }
{
}

//デストラクタ
Clay::~Clay()
{
}

//初期化
void Clay::Initialize()
{
    //モデルデータのロード
    hModel_[0] = Model::Load("/Model/Dish00.fbx");
    assert(hModel_[0] >= 0);

    // 一応あると楽だからここに
    // === 位置のメモ ===
    // (float)(rand() % 10 - 5)
    // X - 1.2～1.2
    // Y 2.0～3.0
    // Z - 6.5～ - 8.0
    transform_.position_ = { 0.0f, 0.0f, 0.0f };  // 位置
    // transform_.position_ = { position_.x,position_.y,position_.z };  // 位置
    transform_.rotate_ = { 0.0f, 0.0f, 0.0f };  // 回転
    transform_.scale_  = { 0.2f, 0.2f, 0.2f };  // 拡大率


    //当たり判定追加
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.8f);
    AddCollider(collision);

}

//更新
void Clay::Update()
{
    Move();
}

void Clay::Move()
{
    //右旋回
    if (Input::IsKey(DIK_O))
    {
        transform_.rotate_.y += 2.5;
    }

    //左旋回
    if (Input::IsKey(DIK_P))
    {
        transform_.rotate_.y -= 2.5;
    }
}

//描画
void Clay::Draw()
{
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);

    // ImGui (デバック用)
    {
        // ======= レティクルの位置座標 =======
        ImGui::Begin("Clay_position");
        ImGui::InputFloat("pos.X", &transform_.position_.x);
        ImGui::InputFloat("pos.Y", &transform_.position_.y);
        ImGui::InputFloat("pos.Z", &transform_.position_.z);
        ImGui::End();
    }
}

void Clay::Release()
{
}

void Clay::OnCollision(GameObject* pTarget)
{
    //弾に当たった
    if (pTarget->GetObjectName() == "Bullet")
    {
        //自分を消す
        KillMe();
    }
}
