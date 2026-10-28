#include "Reticle.hpp"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
#include "Bullet.h"
#include "Engine/Model.h"
#include "Gun.h"

using namespace DirectX;
using namespace std;

// コンストラクタ
Reticle::Reticle(GameObject* parent)
    :GameObject(parent, "Reticle"), position_{ 0.0f,0.0f,0.0f }, hImage_(-1)
{
}

// デストラクタ
Reticle::~Reticle()
{
}

// 初期化
void Reticle::Initialize()
{
    // 銃表示（銃はレティクルの子クラス）
    //Instantiate<Gun>(this);

    // レティクルの画像のロード
    hImage_ = Image::Load("Image/Reticle.png");
    assert(hImage_ >= 0);

    // 一応あると楽だからここに
    // transform_.position_ = { position_.x,position_.y,position_.z };  // 位置
    transform_.rotate_   = { 0.0f,0.0f,0.0f };  // 回転
    transform_.scale_    = { 0.2f, 0.2f,0.2f }; // 拡大率

}

// 更新
void Reticle::Update()
{
    // 標準移動
    Move();

    // 発射
    Shoot();

    // 画面を超えないように指定
    {
        const float Limit_X = 0.9f, Limit_Y = 0.82f;
        if (position_.x <= -Limit_X) position_.x = -Limit_X; // 左
        if (position_.x >=  Limit_X) position_.x =  Limit_X; // 右
        if (position_.y <= -Limit_Y) position_.y = -Limit_Y; // 上
        if (position_.y >=  Limit_Y) position_.y =  Limit_Y; // 下
    }
}

// 描画
void Reticle::Draw()
{
    // レティクル表示
    transform_.position_ = { position_.x,position_.y,position_.z };  // 位置
    Image::SetTransform(hImage_, transform_);
    Image::Draw(hImage_);

    // ImGui (デバック用)
    {
        // ======= レティクルの位置座標 =======
        ImGui::Begin("Reticle_position");
        ImGui::InputFloat("pos.X", &position_.x);
        ImGui::InputFloat("pos.Y", &position_.y);
        ImGui::InputFloat("pos.Z", &position_.z);
        ImGui::End();

        // ======= 発射の状況 =======
        // 右トリガーを一瞬だけ押したときに使う、メンバ変数
        bool triggerOld_ = false;
        bool triggerNow = Input::GetPadTrrigerR(0) > 0.5f;

        ImGui::Begin("Shoot_status");
        if ((Input::IsMouseButtonDown(0)
            || Input::IsPadButtonDown(XINPUT_GAMEPAD_B)
            || triggerNow && !triggerOld_))
        {
            ImGui::Text("Shoot!!");
            ImGui::Text("%.2f", position_.x);
            ImGui::Text("%.2f", position_.y);
        }
        ImGui::End();

        triggerOld_ = triggerNow;

    }
}

// 開放
void Reticle::Release()
{
}

// 標準移動
void Reticle::Move()
{
    float f = 0.02f;

    //移動ベクトル
    XMFLOAT3 moveVector = Input::GetPadStickL();

    // コントローラー対応
    {
        // XMFLOAT3 から float への変換が必要
        position_.x += moveVector.x * f;
        position_.y += moveVector.y * f;
    }

    //前進
    if (Input::IsKey(DIK_W))
    {
        position_.y += f;
    }

    //後退
    if (Input::IsKey(DIK_S))
    {
        position_.y -= f;
    }

    //右旋回
    if (Input::IsKey(DIK_D))
    {
        position_.x += f;
    }

    //左旋回
    if (Input::IsKey(DIK_A))
    {
        position_.x -= f;
    }
}

// 発射
void Reticle::Shoot()
{
    // 右トリガーを一瞬だけ押したときに使う、メンバ変数
    bool triggerOld_ = false;
    bool triggerNow = Input::GetPadTrrigerR(0) > 0.5f;

    if (Input::IsMouseButtonDown(0)
        || Input::IsPadButtonDown(XINPUT_GAMEPAD_B)
        || triggerNow && !triggerOld_)
    {
        //弾をシーンに追加
        GameObject* playScene = FindObject("PlayScene");
        Bullet* pBullet = Instantiate<Bullet>(FindObject("PlayScene"));

        //砲台の先端と根本の位置を取得
        //XMMATRIX shotPos = Image::GetMatrix(hImage_);    //先端
        //XMMATRIX cannonRoot = Image::GetMatrix(hImage_); //根本
        position_.x;

        //撃つ
        pBullet->Shot(transform_.position_, position_);
    }

    triggerOld_ = triggerNow;
}
