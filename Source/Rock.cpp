#include "Rock.hpp"

Rock::Rock(GameObject* parent)
	:Obstacle(parent, "Rock")
{
}

void Rock::Initialize()
{
	hModel_ = Model::Load("Assets/Model/Rock00.fbx");

	SetBoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), { 200, 200, 100 });
}

void Rock::Update()
{
}

void Rock::Release()
{
}
