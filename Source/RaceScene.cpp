#include "RaceScene.hpp"
#include "Horse.hpp"
#include "Stage.hpp"
#include "Fence.hpp"

RaceScene::RaceScene(GameObject* parent)
	:GameObject(parent, "RaceScene")
{
}

void RaceScene::Initialize()
{
	Instantiate<Horse>(this);
	Instantiate<Stage>(this);
	Instantiate<Fence>(this);
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
