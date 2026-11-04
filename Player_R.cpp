#include "Player_R.h"
#include "Engine/Model.h"
#include <cassert>

Player_R::Player_R(GameObject* parent)
	: GameObject(parent, "Player_R")
{
	transform_.position_ = XMFLOAT3(2.0f, 0.0f, 0.0f);
	transform_.scale_ = XMFLOAT3(0.01f, 0.01f, 0.01f);
	transform_.rotate_ = XMFLOAT3(0.0f,270.0f,0.0f);
}

void Player_R::Initialize()
{
	hModel_ = Model::Load("Model/Cowboy02.fbx");
	assert(hModel_ >= 0);
}

void Player_R::Update() {}

void Player_R::Draw()
{
	if (hModel_ < 0) return;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player_R::Release() {}
