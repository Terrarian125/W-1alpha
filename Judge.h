#pragma once

#include "../Engine/GameObject.h"

#include <array>

class Player;

class Judge : public GameObject
{
public:
	Judge(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

	void Judgement();

	inline static int confirmedCount{0};
	inline static std::string winnerName{"None"};

private:
	std::array<Player*, 2> pPlayers_;
};