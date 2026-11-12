#include "cactus1.hpp"

cactus1::cactus1(GameObject* parent)
	:Obstacle(parent, "cactus1")
{
}

void cactus1::Initialize()
{
	hModel_ = Model::Load("Assets/Model/cactus00.fbx");

	SetBoxCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), { 200, 200, 100 });
}

void cactus1::Update()
{
}

void cactus1::Release()
{
}
