#include "ChickenRaceScene.h"

#include "Table.h"
#include "Beermug.h"
#include "Bin.h"
#include "./Engine/Image.h"

ChickenRaceScene::ChickenRaceScene(GameObject *_pParent) :
	GameObject(_pParent, "ChickenRaceScene"),
	hBackGround_(-1)
{
}

void ChickenRaceScene::Initialize()
{
	hBackGround_ = Image::Load("Picture/back_ground.png");
	transform_.scale_ = XMFLOAT3(1.25f, 1.25f, 1.0f);

	Instantiate<Table>(this);
}

void ChickenRaceScene::Update()
{
}

void ChickenRaceScene::Draw()
{
	Image::SetTransform(hBackGround_, transform_);
	Image::Draw(hBackGround_);
}

void ChickenRaceScene::Release()
{
}
