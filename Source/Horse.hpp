#pragma once
#include "../Engine/GameObject.h"

class Horse : public GameObject
{
public:
	Horse(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hModel_;
};