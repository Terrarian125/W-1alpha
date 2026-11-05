#pragma once

#include "../Engine/GameObject.h"

class BackGround : public GameObject
{
public:
	BackGround(GameObject* _pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

private:
	int hImage_;
};