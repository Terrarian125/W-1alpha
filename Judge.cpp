#include "Judge.h"

#include "Player.h"
#include "Stage.h"

Judge::Judge(GameObject *_pParent) :
	GameObject(_pParent, "Judge"),
	pPlayers_()
{
}

void Judge::Initialize()
{
	for (size_t i = 0; i < Stage::MAX_PLAYER_NUM; i++)
	{
		pPlayers_[i] = static_cast<Player*>(FindObject("Player" + std::to_string(i + 1)));
	}
}

void Judge::Update()
{
}

void Judge::Draw()
{
}

void Judge::Release()
{
}

void Judge::Judgement()
{
	float p1WaterLevel = pPlayers_[0]->GetWaterLevel();
	float p2WaterLevel = pPlayers_[1]->GetWaterLevel();

	if (p1WaterLevel > p2WaterLevel)
	{
		winnerName = pPlayers_[0]->GetObjectName();
	}
	else if (fabs(p1WaterLevel - p2WaterLevel) < FLT_EPSILON) // draw
	{
		winnerName = "Draw";
	}
	else
	{
		winnerName = pPlayers_[1]->GetObjectName();
	}
}
