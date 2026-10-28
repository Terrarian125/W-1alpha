#pragma once

#include "../Engine/GameObject.h"

class Beermug : public GameObject
{
public:
	Beermug(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

private:
	int hModel_;
};