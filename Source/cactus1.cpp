#include "cactus1.hpp"

cactus1::cactus1(GameObject* parent)
	:Obstacle(parent)
{
}

void cactus1::Initialize()
{
	hModel_ = Model::Load("Assets/Model/cactus00.fbx");
}

void cactus1::Update()
{
}

void cactus1::Draw()
{
}

void cactus1::Release()
{
}
