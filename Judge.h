#pragma once

#include "../Engine/GameObject.h"

#include <vector>

class Beermug;

class Judge : public GameObject
{
public:
	Judge(GameObject *_pParent);

	void Initialize() override;
	void Update()     override;
	void Draw()       override;
	void Release()    override;

private:
	std::vector<Beermug *> pBeermugs_;

};