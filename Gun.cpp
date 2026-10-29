#include "Gun.h"
#include "ImGui/imgui.h"

#include <DirectXMath.h>
#include "Engine/Model.h"
#include "Engine/Input.h"

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
    position_ = { -3.5f,  -7.0f,  -6.0f }; // 位置
    rotate_   = {  0.0f, -90.0f, -12.0f }; // 回転
    scale_    = {  0.5f,   0.5f,  0.5f };  // 拡大率
}

// 更新
void Gun::Update()
{
    Move();

    // 銃の回転の上限指定
    {
        const float Limit_Y_MAX = -124.0f, Limit_Y_MIN = -60.0f;
        const float Limit_Z_MAX =    8.0f, Limit_Z_MIN = -24.0f;
        if (rotate_.y <= Limit_Y_MAX) rotate_.y = Limit_Y_MAX; // 左
        if (rotate_.y >= Limit_Y_MIN) rotate_.y = Limit_Y_MIN; // 右
        if (rotate_.z >= Limit_Z_MAX) rotate_.z = Limit_Z_MAX; // 上
        if (rotate_.z <= Limit_Z_MIN) rotate_.z = Limit_Z_MIN; // 下
    }
}

// 描画
void Gun::Draw()
{
    //position_ = { -3.5f,  -7.0f, -6.0f };
    transform_.position_ = { position_.x, position_.y, position_.z }; // 位置
    transform_.rotate_   = { rotate_.x, rotate_.y, rotate_.z };       // 回転
    transform_.scale_    = { scale_.x, scale_.y, scale_.z };          // 拡大率

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // ImGui (デバック用)
    {
        //// ======= 銃の位置座標 =======
        //ImGui::Begin("Gun_position");
        //ImGui::InputFloat("pos.X", &position_.x);
        //ImGui::InputFloat("pos.Y", &position_.y);
        //ImGui::InputFloat("pos.Z", &position_.z);
        //ImGui::End();
        //// ======= 銃の回転 =======
        //ImGui::Begin("Gun_rotate");
        //ImGui::InputFloat("rot.X", &rotate_.x);
        //ImGui::InputFloat("rot.Y", &rotate_.y);
        //ImGui::InputFloat("rot.Z", &rotate_.z);
        //ImGui::End();
        //// ======= 銃の拡大率 =======
        //ImGui::Begin("Gun_scale");
        //ImGui::InputFloat("sca.X", &scale_.x);
        //ImGui::InputFloat("sca.Y", &scale_.y);
        //ImGui::InputFloat("sca.Z", &scale_.z);
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
    XMFLOAT3 moveVector = Input::GetPadStickL();

    // コントローラー対応
    {
        // XMFLOAT3 から float への変換が必要
        //rotate_.x += moveVector.x * f;
        //rotate_.y += moveVector.y * f;
    }

    //前進
    if (Input::IsKey(DIK_W))
    {
        rotate_.z += f_z;
    }

    //後退
    if (Input::IsKey(DIK_S))
    {
        rotate_.z -= f_z;
    }

    //右旋回
    if (Input::IsKey(DIK_D))
    {
        rotate_.y += f_y;
    }

    //左旋回
    if (Input::IsKey(DIK_A))
    {
        rotate_.y -= f_y;
    }
}
