#include "Horse.hpp"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

Horse::Horse(GameObject* parent)
	:GameObject(parent, "Horse"), hModel_(-1)
{
}

void Horse::Initialize()
{
	hModel_ = Model::Load("Model/Horse00.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = XMFLOAT3(0, 0, 0);
}

void Horse::Update()
{
	// ジャンプ
	if (Input::IsPadButtonDown(0, XINPUT_GAMEPAD_A))
	{

	}
	// 左右移動
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_LEFT))
	{
		transform_.position_.x -= 0.1f;
	}
	else if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		transform_.position_.x += 0.1f;
	}

	constexpr float backPosition = -1000.0f;
	Camera::SetPosition(XMFLOAT3(0, 400, backPosition));
	Camera::SetTarget(transform_.position_);
}


void Horse::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Horse::Release()
{
}
