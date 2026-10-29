#include "Tumbleweed.hpp"

Tumbleweed::Tumbleweed(GameObject* parent)
	:Obstacle(parent)
{
}

void Tumbleweed::Initialize()
{
	hModel_ = Model::Load("Assets/Model/Tumbleweed00.fbx");
}

void Tumbleweed::Update()
{
}

void Tumbleweed::Draw()
{
}

void Tumbleweed::Release()
{
}
