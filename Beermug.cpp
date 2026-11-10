#include "Beermug.h"
#include "./Engine/Model.h"

#include "WaterLevelHider.h"
#include "Beverage.h"
#include "Bin.h"

#include <imgui.h>

namespace
{
	const float MAX_WATER_LEVEL{ 137.f };
	const float OVERFLOW_RATE{ 1.025f };
}

Beermug::Beermug(GameObject *_pParent) :
	GameObject(_pParent, "Beermug"),
	hModels_(),
	beerMugID_(0),
	waterLevel_(0),
	pWLH_(),
	pBeverage_(),
	isFilling_(false),
	isWLHInstanced_(false)
{
}

void Beermug::Initialize()
{
	pBeverage_ = Instantiate<Beverage>(this);
	beerMugID_ = beerMugCount_;

	hModels_[BEERMUG_CROSS_SECTION_L] = Model::Load("Model/beermug_L.fbx");
	hModels_[BEERMUG_CROSS_SECTION_R] = Model::Load("Model/beermug_R.fbx");
	hModels_[BEERMUG]                 = Model::Load("Model/wood_beermug_mock.fbx");

	beerMugCount_ += 1;
}

void Beermug::Update()
{
	// 注ぎ中
	if (waterLevel_ <= OVERFLOW_RATE)
	{
		if (isFilling_)
		{
			waterLevel_ += 0.0025;
			pBeverage_->SetScale(0.99f, MAX_WATER_LEVEL * waterLevel_, 0.99f);
		}
	}

	// 半分超えた
	if (waterLevel_ >= 0.5f and isWLHInstanced_ == false)
	{
		pWLH_ = Instantiate<WaterLevelHider>(this);
		isWLHInstanced_ = true;
	}

	ImGui::Begin("WL");
	ImGui::InputFloat("WL", &waterLevel_);
	ImGui::End();

	// 溢れた
	if (waterLevel_ >= OVERFLOW_RATE and pWLH_)
	{
		modelIdx_ = 2;
     	if (beerMugID_ % 2 != 0) 
		{
			transform_.rotate_.y = 180.f;
		}

		if (not(pWLH_->IsDead()))
		{
			pWLH_->KillMe();
		}
	}
	isFilling_ = false;
}

void Beermug::Draw()
{
	Model::SetTransform(hModels_[modelIdx_], transform_);
	Model::Draw(hModels_[modelIdx_]);
}

void Beermug::Release()
{
}

void Beermug::Fill()
{
	isFilling_ = true;
}
