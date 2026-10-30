#include "Table.h"
#include "../Engine/Model.h"
#include "Beermug.h"

Table::Table(GameObject *_pParent) :
	GameObject(_pParent, "Table"),
	hModel_(-1)
{
}

void Table::Initialize()
{
	hModel_ = Model::Load("Model/table_mock.fbx");

	transform_.scale_ = XMFLOAT3(7, 7, 7);
	transform_.position_.y = -3;

	for (auto &pBeermug : pBeermugs_)
	{
		pBeermug = Instantiate<Beermug>(this);
	}
	float scale = 0.15f;
	pBeermugs_[0]->SetObjectName("mug1");
	pBeermugs_[0]->SetPosition(XMFLOAT3(-0.3, 0.2, 0));
	pBeermugs_[0]->SetRotate(XMFLOAT3(8, 0, 0));
	pBeermugs_[0]->SetScale(scale);

	pBeermugs_[1]->SetObjectName("mug2");
	pBeermugs_[1]->SetModelIndex(1);
	pBeermugs_[1]->SetPosition(XMFLOAT3(0.3, 0.2, 0));
	pBeermugs_[1]->SetRotate(XMFLOAT3(8, 0, 0));
	pBeermugs_[1]->SetScale(scale);
}

void Table::Update()
{

}

void Table::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Table::Release()
{
}
