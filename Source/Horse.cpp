#include "Horse.hpp"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include <imgui.h>

Horse::Horse(GameObject* parent)
	:GameObject(parent, "Horse"), hModel_(-1), speed_(0.0f), jumpHeight_(0.0f), jumpSpeed_(0.0f), velocity_(0.0f)
{
}

void Horse::Initialize()
{
	hModel_ = Model::Load("Model/Horse00.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = XMFLOAT3(0, 0, 0);

	speed_ = 0.5f;
}

void Horse::Update()
{
	transform_.position_.z += speed_;
	
	if (speed_ < 5.0f)
	{
		speed_ += 0.01f;
	}

	// ジャンプ
	if (Input::IsPadButtonDown(0, XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_SPACE))
	{
		
	}
	// 左右移動
	if (transform_.position_.x < -400.0f)
	{
		transform_.position_.x = -400.0f;
	}
	else if (transform_.position_.x > 400.0f)
	{
		transform_.position_.x = 400.0f;
	}
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_LEFT) || Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 5.0f;
	}
	else if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_RIGHT) || Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 5.0f;
	}
	else
	{

	}

	constexpr float upPosition = 500.0f;
	constexpr float backPosition = -500.0f;
	Camera::SetPosition(XMFLOAT3(0, transform_.position_.y + upPosition, transform_.position_.z + backPosition));
	

	float targetPositionX = 0;
	float targetPositionY = transform_.position_.y + 200.0f;
	float targetPositionZ = transform_.position_.z + 100.0f;
	Camera::SetTarget(XMFLOAT3(targetPositionX, targetPositionY, targetPositionZ));

	ImGui::Begin("Horse Info");
	ImGui::InputFloat("Position X", &transform_.position_.x);
	ImGui::InputFloat("Position Y", &transform_.position_.y);
	ImGui::InputFloat("Position Z", &transform_.position_.z);
	ImGui::InputFloat("Speed", &speed_);
	ImGui::End();
}


void Horse::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Horse::Release()
{
}
