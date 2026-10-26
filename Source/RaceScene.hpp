#pragma once
#include "../Engine/GameObject.h"

class RaceScene : public GameObject
{
public:
	RaceScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
};