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
    hModel_[0] = Model::Load("/Model/Bullet.fbx");
    assert(hModel_[0] >= 0);

    // 一応あると楽だからここに
    // transform_.position_ = { position_.x,position_.y,position_.z };  // 位置
    transform_.rotate_ = { 0.0f,0.0f,0.0f };  // 回転
    transform_.scale_ = { 0.2f, 0.2f,0.2f }; // 拡大率

    //サイズ
    transform_.scale_ = { 0.2f, 0.2f,0.2f }; // 拡大率

    //  (float)(rand() % 10 - 5)
    //位置
    transform_.position_ = { 0,0, 0};  // 位置

}

//更新
void Clay::Update()
{
    Move();
}

void Clay::Move()
{
    //戦車が向いている方向に回転させる行列
    XMMATRIX rotateMatrix = XMMatrixRotationY(transform_.rotate_.vecY / 180 * 3.14f);

    //移動ベクトル
    XMVECTOR  moveVector = XMVector3TransformCoord(XMVectorSet(0, 0, 0.2f, 0), rotateMatrix);

    //コントローラー対応
    //transform_.position_ += Input::GetPadStickL();
    //transform_.position_ -= Input::GetPadStickL();

    //右旋回
    if (Input::IsKey(DIK_O))
    {
        transform_.rotate_.vecY += 2.5;
    }

    //左旋回
    if (Input::IsKey(DIK_P))
    {
        transform_.rotate_.vecY -= 2.5;
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
        ImGui::InputFloat("pos.X", &transform_.position_.vecX);
        ImGui::InputFloat("pos.Y", &transform_.position_.vecY);
        ImGui::InputFloat("pos.Z", &transform_.position_.vecZ);
        ImGui::End();
    }
}

void Clay::Release()
{
}
