#pragma once

#include "../Engine/GameObject.h"

class Beermug;

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

	void Pouring();
	void Conform();

private:
	int  hModel_;

	int  pouringTime_;
	bool isPouring_;
	bool isConfirmed_;

	Beermug* pBeermug_;
	bool  beermugInstanceRetrieved_;

};