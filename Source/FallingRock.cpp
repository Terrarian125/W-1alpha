#include "FallingRock.hpp"

FallingRock::FallingRock(GameObject* parent)
	:Obstacle(parent)
{
}

void FallingRock::Initialize()
{
	hModel_ = Model::Load("Assets/Model/FallingRock01.fbx");
}

void FallingRock::Update()
{
}

void FallingRock::Draw()
{
}

void FallingRock::Release()
{
}
