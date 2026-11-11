#pragma once
#include "../Engine/GameObject.h"
#include "Horse.hpp"
#include "Fence.hpp"

class Stage : public GameObject
{
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hModel_;
	Horse* horse;
	Fence* fence;
};