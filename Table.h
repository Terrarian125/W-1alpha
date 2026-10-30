#pragma once

#include "../Engine/GameObject.h"
#include <array>

class Beermug;

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
	std::array<Beermug *, 2> pBeermugs_;
};