#include "RaceScene.hpp"
#include "Horse.hpp"
#include "Stage.hpp"
#include "../Engine/Image.h"
#include "Fence.hpp"

RaceScene::RaceScene(GameObject* parent)
	:GameObject(parent, "RaceScene"), hImage_(-1)
{
}

void RaceScene::Initialize()
{
	hImage_ = Image::Load("Picture/yuuhi.jpg");

	Instantiate<Horse>(this);
	Instantiate<Stage>(this);
	//Instantiate<Fence>(this);
}

void RaceScene::Update()
{
}

void RaceScene::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
}

void RaceScene::Release()
{
}
