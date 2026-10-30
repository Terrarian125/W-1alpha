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

	void SetModelIndex(int _index)
	{
		if (_index > 2)
		{
			return;
		}
		modelIdx_ = _index;
	}

private:
	int hModels_[2];
	int modelIdx_ = 0;
};