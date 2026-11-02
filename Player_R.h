#pragma once

#include "Engine/GameObject.h"

class Player_R : public GameObject
{
public:
	Player_R(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_ = -1;
};
