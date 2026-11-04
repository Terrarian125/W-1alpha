#pragma once

#include "../Engine/GameObject.h"

class WaterLevelHider;
class Beverage;
class Bin;

class Beermug : public GameObject
{
public:
	Beermug(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

	void SetModelIndex(int _index)
	{
		if (_index > 2)
		{
			return;
		}
		modelIdx_ = _index;
	}

	float GetWaterLevel()
	{
		return waterLevel_;
	}

private:
	int hModels_[3];
	int modelIdx_ = 0;

	WaterLevelHider *pWLH_;
	Beverage *pBeverage_;
	Bin *pBin_;

	float waterLevel_;
};