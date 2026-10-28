#pragma once

#include "../Engine/GameObject.h"

class Table : public GameObject
{
public:
	Table(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

private:
	int hModel_;
};