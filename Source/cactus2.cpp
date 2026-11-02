#include "cactus2.hpp"

cactus2::cactus2(GameObject* parent)
	:Obstacle(parent)
{
}

void cactus2::Initialize()
{
	hModel_ = Model::Load("Assets/Model/cactus01.fbx");
}

void cactus2::Update()
{
}

void cactus2::Draw()
{
}

void cactus2::Release()
{
}
