#pragma once

#include "../Engine/GameObject.h"

#include <map>

#include "PlayerAction.h"

struct InputBinding;

class Bin;
class Beermug;

class Player : public GameObject
{
public:
	Player(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

	std::map<PlayerAction, InputBinding>& InputSet()
	{
		return inputSet_;
	}

	int GetPlayerID()
	{
		return playerID_;
	}

private:
	// Zero origin
	inline static int playerCount_{0};

	int playerID_;
	std::map<PlayerAction, InputBinding> inputSet_;
	
	Bin* pBin_;
	Beermug* pBeermug_;
};