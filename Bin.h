#pragma once

#include "../Engine/GameObject.h"

class Bin : public GameObject
{
public:
	Bin(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

	bool IsPouring()
	{
		return isPouring_;
	}

private:
	int hModel_;
	bool isPouring_;
};