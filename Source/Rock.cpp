#include "Rock.hpp"

Rock::Rock(GameObject* parent)
	:Obstacle(parent)
{
}

void Rock::Initialize()
{
	hModel_ = Model::Load("Assets/Model/Rock00.fbx");
}

void Rock::Update()
{
}

void Rock::Draw()
{
}

void Rock::Release()
{
}
