#include "Transform.h"



Transform::Transform(): pParent_(nullptr)
{
	position_ = XMVectorSet(0, 0, 0, 0);
	rotate_ = XMVectorSet(0, 0, 0, 0);
	scale_ = XMVectorSet(1, 1, 1, 0);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}


Transform::~Transform()
{
}

void Transform::Calclation()
{
	//ˆÚ“®s—ñ
	matTranslate_ = XMMatrixTranslation(position_.vecX, position_.vecY, position_.vecZ);

	//‰ñ“]s—ñ
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.vecX));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.vecY));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.vecZ));
	matRotate_ = rotateZ * rotateX * rotateY;

	//Šg‘åk¬
	matScale_ = XMMatrixScaling(scale_.vecX, scale_.vecY, scale_.vecZ);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	if (pParent_)
	{
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}

