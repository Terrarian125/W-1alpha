#include "RaceScene.hpp"
#include "Horse.hpp"

RaceScene::RaceScene(GameObject* parent)
	:GameObject(parent, "RaceScene")
{
}

void RaceScene::Initialize()
{
	Instantiate<Horse>(this);
}

void RaceScene::Update()
{
}

void RaceScene::Draw()
{
}

void RaceScene::Release()
{
}
