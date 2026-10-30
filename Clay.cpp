#include "Clay.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
using namespace DirectX;

//コンストラクタ
Clay::Clay(GameObject* parent)
    :GameObject(parent, "Clay"), position_{ { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f } }, hModel_{ (-1,-1,-1) }, On_down{ true, true, false }
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

    position_[0] = { 0.0f, 3.0f, 0.0f }; // 位置
    rotate_[0]   = { 0.0f, 0.0f, 0.0f }; // 回転
    scale_[0]    = { 0.2f, 0.2f, 0.2f }; // 拡大率

    position_[1] = { 0.8f, 1.0f, 0.0f }; // 位置
    rotate_[1]   = { 0.0f, 0.0f, 0.0f }; // 回転
    scale_[1]    = { 0.2f, 0.2f, 0.2f }; // 拡大率

    position_[2] = { -0.4f, 0.0f, 0.2f }; // 位置
    rotate_[2]   = { 0.0f, 0.0f, 0.0f }; // 回転
    scale_[2]    = { 0.2f, 0.2f, 0.2f }; // 拡大率

    //当たり判定追加
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.1f, 0.0f), 0.8f);
    AddCollider(collision);

}

//更新
void Clay::Update()
{
    Move();


    // 銃の回転の上限指定
    {
        const float Limit_X_MAX = -12.0f, Limit_X_MIN = 12.0f;
        const float Limit_Y_MAX = 2.5f, Limit_Y_MIN = -2.5f;

        // クレー１
        {
            if (position_[0].x < Limit_X_MAX) position_[0].x = Limit_X_MIN; // 左から右
            if (position_[0].x > Limit_X_MIN) position_[0].x = Limit_X_MAX; // 右から左
        }

        // クレー２
        {
            if (position_[1].x < Limit_X_MAX) position_[1].x = Limit_X_MIN; // 左から右
            if (position_[1].x > Limit_X_MIN) position_[1].x = Limit_X_MAX; // 右から左
            if (position_[1].y > Limit_Y_MAX) {
                On_down[1] = true; // 降下中
                position_[1].y = Limit_Y_MAX; // 上から下
            }
            if (position_[1].y < Limit_Y_MIN) {
                On_down[1] = false; // 上昇
                position_[1].y = Limit_Y_MIN; // 下から上
            }
        }

        // クレー３
        {
            if (position_[2].x < Limit_X_MAX) position_[2].x = Limit_X_MIN; // 左から右
            if (position_[2].x > Limit_X_MIN) position_[2].x = Limit_X_MAX; // 右から左
            if (position_[2].y > Limit_Y_MAX) {
                On_down[2] = true; // 降下中
                position_[2].y = Limit_Y_MAX; // 上から下
            }
            if (position_[2].y < Limit_Y_MIN) {
                On_down[2] = false; // 上昇
                position_[2].y = Limit_Y_MIN; // 下から上
            }
        }
    }
}

void Clay::Move()
{
    //右旋回
    if (Input::IsKey(DIK_O))
    {
        //rotate_[0].x += 2.5f;
    }

    //左旋回
    if (Input::IsKey(DIK_P))
    {
       //rotate_[0].x -= 2.5f;
       //position_[1].y -= 2.5f;
    }

    position_[0].x += 0.15f;
    rotate_[0].x += 2.5f;
    rotate_[0].y += 5.0f;

    position_[1].x -= 0.15f;
    rotate_[1].x -= 1.0f;
    if(On_down[1]) position_[1].y -= 0.02f;
    else position_[1].y += 0.02f;

    position_[2].x += 0.30f;
    if (On_down[2]) position_[2].y -= 0.5f;
    else position_[2].y += 0.5f;
}

//描画
void Clay::Draw()
{
    // クレー表示
    transform_.position_ = { position_[0].x, position_[0].y, position_[0].z};   // 位置
    transform_.rotate_   = { rotate_[0].x, rotate_[0].y, rotate_[0].z };        // 回転
    transform_.scale_    = { scale_[0].x, scale_[0].y, scale_[0].z };           // 拡大率
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);

    transform_.position_ = { position_[1].x, position_[1].y, position_[1].z };   // 位置
    transform_.rotate_ = { rotate_[1].x, rotate_[1].y, rotate_[1].z };           // 回転
    transform_.scale_ = { scale_[1].x, scale_[1].y, scale_[1].z };               // 拡大率
    Model::SetTransform(hModel_[1], transform_);
    Model::Draw(hModel_[1]);

    transform_.position_ = { position_[2].x, position_[2].y, position_[2].z };   // 位置
    transform_.rotate_ = { rotate_[2].x, rotate_[2].y, rotate_[2].z };           // 回転
    transform_.scale_ = { scale_[2].x, scale_[2].y, scale_[2].z };               // 拡大率
    Model::SetTransform(hModel_[2], transform_);
    Model::Draw(hModel_[2]);

    // ImGui (デバック用)
    {
        // ======= クレーの位置座標 =======
        ImGui::Begin("Clay_position");
        ImGui::InputFloat("pos.X1", &position_[0].x);
        ImGui::InputFloat("pos.Y1", &position_[0].y);
        ImGui::InputFloat("pos.Z1", &position_[0].z);
        ImGui::InputFloat("pos.X2", &position_[1].x);
        ImGui::InputFloat("pos.Y2", &position_[1].y);
        ImGui::InputFloat("pos.Z2", &position_[1].z);
        ImGui::InputFloat("pos.X3", &position_[2].x);
        ImGui::InputFloat("pos.Y3", &position_[2].y);
        ImGui::InputFloat("pos.Z3", &position_[2].z);
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
