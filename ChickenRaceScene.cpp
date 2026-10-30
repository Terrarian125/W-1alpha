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
	transform_.scale_ = XMFLOAT3(1.2f, 1.25f, 1.0f);

	Instantiate<Table>(this);


	Bin *bin1{};
	Bin *bin2{};
	bin1 = Instantiate<Bin>(this);
	bin2 = Instantiate<Bin>(this);

	bin1->SetObjectName("bin1");
	bin1->SetPosition(XMFLOAT3(-4, 0, -3));
	bin1->SetRotate(XMFLOAT3(10, 0, -20));
	bin1->SetScale(0.75);

	bin2->SetObjectName("bin2");
	bin2->SetPosition(XMFLOAT3(4, 0, -3));
	bin2->SetRotate(XMFLOAT3(-10, 180, -20));
	bin2->SetScale(0.75);
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
