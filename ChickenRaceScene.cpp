#include "ChickenRaceScene.h"

#include "Table.h"
#include "Beermug.h"
#include "Bin.h"
#include "BackGround.h"

#include "./Engine/Camera.h"

ChickenRaceScene::ChickenRaceScene(GameObject *_pParent) :
	GameObject(_pParent, "ChickenRaceScene")
{
}

void ChickenRaceScene::Initialize()
{
	XMFLOAT3 camPos{0.f, 0.f, -10.f};
	Camera::SetPosition(camPos);

	Instantiate<BackGround>(this);
	Instantiate<Table>(this);
}

void ChickenRaceScene::Update()
{
}

void ChickenRaceScene::Draw()
{
}

void ChickenRaceScene::Release()
{
}
