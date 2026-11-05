#include "Beermug.h"
#include "./Engine/Model.h"

#include "WaterLevelHider.h"
#include "Beverage.h"
#include "Bin.h"

#include <imgui.h>

namespace
{
	bool wlhInstanced = false;
	float MAX_WATER_LEVEL{ 140 };
	float SAFE_WATER_LEVEL{ 135 };
}

Beermug::Beermug(GameObject *_pParent) :
	GameObject(_pParent, "Beermug"),
	hModels_(),
	waterLevel_(0),
	pBeverage_(),
	pBin_()
{
}

void Beermug::Initialize()
{
	pBeverage_ = Instantiate<Beverage>(this);

	hModels_[BEERMUG_CROSS_SECTION_L] = Model::Load("Model/beermug_L.fbx");
	hModels_[BEERMUG_CROSS_SECTION_R] = Model::Load("Model/beermug_R.fbx");
	hModels_[BEERMUG]                 = Model::Load("Model/wood_beermug_mock.fbx");

	pBin_ = static_cast<Bin*>(FindObject("Bin" + std::to_string(beerMugID_)));
	beerMugID_ += 1;
}

void Beermug::Update()
{
	// 注ぎ中
	if (waterLevel_ <= 1.0f)
	{
		if (pBin_->IsPouring())
		{
			waterLevel_ += 0.0025;
			pBeverage_->SetScale(0.99f, MAX_WATER_LEVEL * waterLevel_, 0.99f);
		}
	}

	// 半分超えた
	if (waterLevel_ >= 0.5f and wlhInstanced == false)
	{
		pWLH_ = Instantiate<WaterLevelHider>(this);
		wlhInstanced = true;
	}

	// 溢れた
	if (waterLevel_ >= 1.0f and pWLH_)
	{
		modelIdx_ = 2;
		if (not(pWLH_->IsDead()))
		{
			pWLH_->KillMe();
		}
	}
}

void Beermug::Draw()
{
	Model::SetTransform(hModels_[modelIdx_], transform_);
	Model::Draw(hModels_[modelIdx_]);
}

void Beermug::Release()
{
}
