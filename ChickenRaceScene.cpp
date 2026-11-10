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

	// pJudge_ = Instantiate<Judge>(this);
}

void ChickenRaceScene::Update()
{
	/* if (confirmedConut == 2)
	{
		pJudge_.Judgement();
		
	}
	*/
}

void ChickenRaceScene::Draw()
{
}

void ChickenRaceScene::Release()
{
}
