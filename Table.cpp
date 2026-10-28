#include "Table.h"
#include "../Engine/Model.h"

Table::Table(GameObject *_pParent) :
	GameObject(_pParent, "Table"),
	hModel_(-1)
{
}

void Table::Initialize()
{
	hModel_ = Model::Load("Model/table_mock.fbx");

	transform_.scale_ = XMFLOAT3(7, 1, 5);
	transform_.position_.y = -3;
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
