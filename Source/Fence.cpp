#include "Fence.hpp"

Fence::Fence(GameObject* parent)
	:Obstacle(parent, "Fence")
{
}

void Fence::Initialize()
{
	hModel_ = Model::Load("Model/Fence00.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = XMFLOAT3(0, 0, 1000);
}

void Fence::Update()
{
}

void Fence::Release()
{
}
