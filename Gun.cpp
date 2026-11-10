#include "Gun.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
#include "Engine/Model.h"
#include "Engine/Input.h"

using namespace DirectX;
using namespace std;

// コンストラクタ
Gun::Gun(GameObject* parent)
    :GameObject(parent, "Reticle"), position_{ {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} }, hModel_(-1)
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
    position_[0] = { -3.5f,  -7.0f,  -6.0f}; // 位置
    rotate_[0] = { 0.0f, -103.0f, -12.0f}; // 回転
    scale_[0] = { 0.5f,   0.5f,  0.5f};  // 拡大率

    position_[1] = { 3.8f,  -7.0f,  -6.0f }; // 位置
    rotate_[1] = { 0.0f, -77.0f, -12.0f }; // 回転
    scale_[1] = { 0.5f,   0.5f,  0.5f };  // 拡大率

    textGun_.Initialize("Fonts/Rye-Regular.ttf", 28.0f);
}

// 更新
void Gun::Update()
{
    Move();

    // 銃の回転の上限指定
    {
        const float Limit_Y_MAX = -124.0f, Limit_Y_MIN = -60.0f;
        const float Limit_Z_MAX = 8.0f, Limit_Z_MIN = -24.0f;
        for (int i = 0; i < 2; i++) {
            if (rotate_[i].y <= Limit_Y_MAX) rotate_[i].y = Limit_Y_MAX; // 左
            if (rotate_[i].y >= Limit_Y_MIN) rotate_[i].y = Limit_Y_MIN; // 右
            if (rotate_[i].z >= Limit_Z_MAX) rotate_[i].z = Limit_Z_MAX; // 上
            if (rotate_[i].z <= Limit_Z_MIN) rotate_[i].z = Limit_Z_MIN; // 下
        }
    }
}

// 描画
void Gun::Draw()
{
    //position_ = { -3.5f,  -7.0f, -6.0f };
    transform_.position_ = { position_[0].x, position_[0].y, position_[0].z}; // 位置
    transform_.rotate_   = { rotate_[0].x, rotate_[0].y, rotate_[0].z};       // 回転
    transform_.scale_    = { scale_[0].x, scale_[0].y, scale_[0].z};          // 拡大率

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    transform_.position_ = { position_[1].x, position_[1].y, position_[1].z }; // 位置
    transform_.rotate_ = { rotate_[1].x, rotate_[1].y, rotate_[1].z };       // 回転
    transform_.scale_ = { scale_[1].x, scale_[1].y, scale_[1].z };          // 拡大率

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // ImGui (デバック用)
    {
        //// ======= 銃の位置座標 =======
        //ImGui::Begin("Gun_position");
        //ImGui::InputFloat("pos.X", &position_[0].x);
        //ImGui::InputFloat("pos.Y", &position_[0].y);
        //ImGui::InputFloat("pos.Z", &position_[0].z);
        //ImGui::End();
        //// ======= 銃の回転 =======
        //ImGui::Begin("Gun_rotate");
        //ImGui::InputFloat("rot.X", &rotate_[0].x);
        //ImGui::InputFloat("rot.Y", &rotate_[0].y);
        //ImGui::InputFloat("rot.Z", &rotate_[0].z);
        //ImGui::End();
        //// ======= 銃の拡大率 =======
        //ImGui::Begin("Gun_scale");
        //ImGui::InputFloat("sca.X", &scale_[0].x);
        //ImGui::InputFloat("sca.Y", &scale_[0].y);
        //ImGui::InputFloat("sca.Z", &scale_[0].z);
        //ImGui::End();
    }
}

void Gun::Release()
{
}

void Gun::Move()
{
    float f_z = 0.5f, f_y = 0.7f;

    //移動ベクトル
    XMFLOAT3 moveVector[2] = { Input::GetPadStickL(0), Input::GetPadStickL(1) };

    // コントローラー対応
    {
        // XMFLOAT3 から float への変換が必要
        rotate_[0].z += moveVector[0].y * f_z;
        rotate_[0].y += moveVector[0].x * f_y;

        rotate_[1].z += moveVector[1].y * f_z;
        rotate_[1].y += moveVector[1].x * f_y;
    }

    //前進
    if (Input::IsKey(DIK_W))
    {
        rotate_[0].z += f_z;
    }

    //後退
    if (Input::IsKey(DIK_S))
    {
        rotate_[0].z -= f_z;
    }

    //右旋回
    if (Input::IsKey(DIK_D))
    {
        rotate_[0].y += f_y;
    }

    //左旋回
    if (Input::IsKey(DIK_A))
    {
        rotate_[0].y -= f_y;
    }

    // ↓デバック用
    {
        //前進
        if (Input::IsKey(DIK_I))
        {
            rotate_[1].z += f_z;
        }

        //後退
        if (Input::IsKey(DIK_K))
        {
            rotate_[1].z -= f_z;
        }

        //右旋回
        if (Input::IsKey(DIK_L))
        {
            rotate_[1].y += f_y;
        }

        //左旋回
        if (Input::IsKey(DIK_J))
        {
            rotate_[1].y -= f_y;
        }
    }
}
