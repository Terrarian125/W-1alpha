#include "Horse.hpp"
#include "../Engine/Input.h"
#include "../Engine/Model.h"

Horse::Horse(GameObject* parent)
	:GameObject(parent, "Horse"), hModel_(-1)
{
}

void Horse::Initialize()
{
	hModel_ = Model::Load("Assets/Model/Horse00.fbx");
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
}


void Horse::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Horse::Release()
{
}
