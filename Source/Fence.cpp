#include "Fence.hpp"

Fence::Fence(GameObject* parent)
	:Obstacle(parent)
{
}

void Fence::Initialize()
{
	hModel_ = Model::Load("Assets/Model/Fence00.fbx");
}

void Fence::Update()
{
}

void Fence::Draw()
{
}

void Fence::Release()
{
}
