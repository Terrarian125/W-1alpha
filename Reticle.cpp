#include "Reticle.hpp"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
//#include "Bullet.h"
#include "Engine/Model.h"
#include "Gun.h"
#include "UI.h"
#include "Clay.h"

using namespace DirectX;
using namespace std;

// コンストラクタ
Reticle::Reticle(GameObject* parent)
    :GameObject(parent, "Reticle"), position_{ {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} }, hImage_{ -1,-1 }
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
    hImage_[0] = Image::Load("Image/Reticle.png");
    assert(hImage_[0] >= 0);
    hImage_[1] = Image::Load("Image/Reticle_2P.png");
    assert(hImage_[1] >= 0);

    // 一応あると楽だからここに
    position_[0] = { -0.3f, 0.0f, 0.0f };  // 位置
    position_[1] = {  0.3f, 0.0f, 0.0f };  // 位置
    rotate_   = { 0.0f,0.0f,0.0f };  // 回転
    scale_    = { 0.2f, 0.2f,0.2f }; // 拡大率

    textReticle_.Initialize("Fonts/Rye-Regular.ttf", 28.0f);
}

// 更新
void Reticle::Update()
{
    // 標準移動
    Move();

    // 発射
    Shoot_1P();
    Shoot_2P();

    // 画面を超えないように指定
    {
        const float Limit_X_MAX =  -0.9f, Limit_X_MIN =  0.9f;
        const float Limit_Y_MAX =  0.82f, Limit_Y_MIN = -0.5f;
        for (int i = 0; i < 2; i++) {
            if (position_[i].x <= Limit_X_MAX) position_[i].x = Limit_X_MAX; // 左
            if (position_[i].x >= Limit_X_MIN) position_[i].x = Limit_X_MIN; // 右
            if (position_[i].y >= Limit_Y_MAX) position_[i].y = Limit_Y_MAX; // 上
            if (position_[i].y <= Limit_Y_MIN) position_[i].y = Limit_Y_MIN; // 下
        }
    }
}

// 描画
void Reticle::Draw()
{
    transform_.rotate_ = { rotate_.x, rotate_.y, rotate_.z };      // 回転
    transform_.scale_ = { scale_.x, scale_.y, scale_.z };          // 拡大率

    // レティクル表示
    transform_.position_ = { position_[0].x,position_[0].y,position_[0].z};  // 位置
    Image::SetTransform(hImage_[0], transform_);
    Image::Draw(hImage_[0]);

    transform_.position_ = { position_[1].x,position_[1].y,position_[1].z };  // 位置
    Image::SetTransform(hImage_[1], transform_);
    Image::Draw(hImage_[1]);

    // ImGui (デバック用)
    {
        /*
        // ======= レティクルの位置座標 =======
        ImGui::Begin("Reticle_position");
        ImGui::InputFloat("pos1P.X", &position_[0].x);
        ImGui::InputFloat("pos1P.Y", &position_[0].y);
        ImGui::InputFloat("pos2P.X", &position_[1].x);
        ImGui::InputFloat("pos2P.Y", &position_[1].y);
        //ImGui::InputFloat("pos.Z", &position_.z);
        ImGui::End();
        // ======= 発射の状況 =======
        // 右トリガーを一瞬だけ押したときに使う、メンバ変数
        bool triggerNow[2] = { Input::GetPadTrrigerR(0) > 0.5f, Input::GetPadTrrigerR(1) > 0.5f };

        ImGui::Begin("Shoot_status");
        if ((Input::IsMouseButtonDown(0)
            || Input::IsPadButtonDown(XINPUT_GAMEPAD_B, 0)
            || triggerNow[0] && !triggerOld_[0]))
        {
            ImGui::Text("Shoot!!");
            ImGui::Text("%.2f", position_[0].x);
            ImGui::Text("%.2f", position_[0].y);
        }
        if ((Input::IsMouseButtonDown(1)
            || Input::IsPadButtonDown(XINPUT_GAMEPAD_B, 1)
            || triggerNow[1] && !triggerOld_[1]))
        {
            ImGui::Text("Shoot!!");
            ImGui::Text("%.2f", position_[1].x);
            ImGui::Text("%.2f", position_[1].y);
        }
        ImGui::End();

        triggerOld_[0] = triggerNow[0];
        triggerOld_[1] = triggerNow[1];
        */
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
    XMFLOAT3 moveVector[2] = { Input::GetPadStickL(0), Input::GetPadStickL(1) };

    // コントローラー対応
    {
        // XMFLOAT3 から float への変換が必要
        position_[0].x += moveVector[0].x * f;
        position_[0].y += moveVector[0].y * f;

        position_[1].x += moveVector[1].x * f;
        position_[1].y += moveVector[1].y * f;
    }

    //前進
    if (Input::IsKey(DIK_W))
    {
        position_[0].y += f;
    }

    //後退
    if (Input::IsKey(DIK_S))
    {
        position_[0].y -= f;
    }

    //右旋回
    if (Input::IsKey(DIK_D))
    {
        position_[0].x += f;
    }

    //左旋回
    if (Input::IsKey(DIK_A))
    {
        position_[0].x -= f;
    }

    // ↓デバック用
    {
        //前進
        if (Input::IsKey(DIK_I))
        {
            position_[1].y += f;
        }

        //後退
        if (Input::IsKey(DIK_K))
        {
            position_[1].y -= f;
        }

        //右旋回
        if (Input::IsKey(DIK_L))
        {
            position_[1].x += f;
        }

        //左旋回
        if (Input::IsKey(DIK_J))
        {
            position_[1].x -= f;
        }
    }
}

// 発射
void Reticle::Shoot_1P()
{
    // 右トリガーを一瞬だけ押したときに使う、メンバ変数
    bool triggerNow = Input::GetPadTrrigerR(0) > 0.5f;

    if (Input::IsMouseButtonDown(0)
        || Input::IsPadButtonDown(XINPUT_GAMEPAD_B, 0)
        || triggerNow && !triggerOld_[0])
    {
        // クレーとの当たり判定
        Clay* pClay = static_cast<Clay*>(FindObject("Clay"));
        if (pClay != nullptr) {
            pClay->TryBreak_1P(XMFLOAT2(position_[0].x, position_[0].y));
        }

        //弾をシーンに追加
        //GameObject* playScene = FindObject("PlayScene");
        //Bullet* pBullet = Instantiate<Bullet>(FindObject("PlayScene"));

        //発射方向 = 先端 - 根本
        //XMFLOAT3 dir;
        //XMStoreFloat3(&dir, XMLoadFloat3(&position_) - XMLoadFloat3(&rotate_));

        //砲台の先端と根本の位置を取得
        //XMMATRIX shotPos = Image::GetMatrix(hImage_);    //先端
        //XMMATRIX cannonRoot = Image::GetMatrix(hImage_); //根本
        // position_.x;

        //撃つ
        //pBullet->Shot(position_, dir);
    }

    triggerOld_[0] = triggerNow;
}

// 発射
void Reticle::Shoot_2P()
{
    // 右トリガーを一瞬だけ押したときに使う、メンバ変数
    bool triggerNow = Input::GetPadTrrigerR(1) > 0.5f;

    if (Input::IsMouseButtonDown(1)
        || Input::IsPadButtonDown(XINPUT_GAMEPAD_B, 1)
        || triggerNow && !triggerOld_[1])
    {
        // クレーとの当たり判定
        Clay* pClay = static_cast<Clay*>(FindObject("Clay"));
        if (pClay != nullptr) {
            pClay->TryBreak_2P(XMFLOAT2(position_[1].x, position_[1].y));
        }
    }

    triggerOld_[1] = triggerNow;
}
