#include "Stage.hpp"
#include "../Engine/Model.h"
#include "Fence.hpp"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1)
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Model/Game04_StageFloor00.fbx");
	//assert(hModel_ >= 0);
	transform_.position_ = XMFLOAT3(0, 0, 0);
	transform_.scale_ = XMFLOAT3(1, 1, 50);

	horse = Instantiate<Horse>(GetParent());
	fence = Instantiate<Fence>(GetParent());
}

void Stage::Update()
{
	horse->Collision(fence);
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
}
