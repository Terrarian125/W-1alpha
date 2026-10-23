#include "Horse.hpp"
#include "../Engine/Input.h"

Horse::Horse(GameObject* parent)
	:GameObject(parent, "Horse"), hModel_(-1)
{
}

void Horse::Initialize()
{
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
	}
	else if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
	}
}


void Horse::Draw()
{
}

void Horse::Release()
{
}
