#include "Rock.hpp"

Rock::Rock(GameObject* parent)
	:Obstacle(parent, "Rock")
{
}

void Rock::Initialize()
{
	hModel_ = Model::Load("Assets/Model/Rock00.fbx");
}

void Rock::Update()
{
}

void Rock::Release()
{
}
