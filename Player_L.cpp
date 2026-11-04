#include "Player_L.h"
#include "Engine/Model.h"
#include <cassert>

Player_L::Player_L(GameObject* parent)
	: GameObject(parent, "Player_L")
{
	transform_.position_ = XMFLOAT3(-2.0f, 0.0f, 0.0f);
	transform_.scale_ = XMFLOAT3(0.01f, 0.01f, 0.01f);
	transform_.rotate_ = XMFLOAT3(0.0f, 90.0f, 0.0f);
}

void Player_L::Initialize()
{
	hModel_ = Model::Load("Model/Cowboy01.fbx");
	assert(hModel_ >= 0);
}

void Player_L::Update() {}

void Player_L::Draw()
{
	if (hModel_ < 0) return;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player_L::Release() {}
