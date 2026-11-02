#include "Obstacle.hpp"
#include "../Engine/Model.h"

Obstacle::Obstacle(GameObject* parent)
	:GameObject(parent, "Obstacle"), hModel_(-1)
{  
}

void Obstacle::Initialize()
{
}

void Obstacle::Update()
{
}

void Obstacle::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Obstacle::Release()
{
}
