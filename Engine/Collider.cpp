#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"

//コンストラクタ
Collider::Collider():
	pGameObject_(nullptr)
{
}

//デストラクタ
Collider::~Collider()
{
}

//箱型同士の衝突判定
//引数：boxA	１つ目の箱型判定
//引数：boxB	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	XMVECTOR boxPosA = boxA->pGameObject_->GetPosition() + boxA->center_;
	XMVECTOR boxPosB = boxB->pGameObject_->GetPosition() + boxB->center_;


	if ((boxPosA.vecX + boxA->size_.vecX / 2) > (boxPosB.vecX - boxB->size_.vecX / 2) &&
		(boxPosA.vecX - boxA->size_.vecX / 2) < (boxPosB.vecX + boxB->size_.vecX / 2) &&
		(boxPosA.vecY + boxA->size_.vecY / 2) > (boxPosB.vecY - boxB->size_.vecY / 2) &&
		(boxPosA.vecY - boxA->size_.vecY / 2) < (boxPosB.vecY + boxB->size_.vecY / 2) &&
		(boxPosA.vecZ + boxA->size_.vecZ / 2) > (boxPosB.vecZ - boxB->size_.vecZ / 2) &&
		(boxPosA.vecZ - boxA->size_.vecZ / 2) < (boxPosB.vecZ + boxB->size_.vecZ / 2))
	{
		return true;
	}
	return false;
}

//箱型と球体の衝突判定
//引数：box	箱型判定
//引数：sphere	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMVECTOR circlePos = sphere->pGameObject_->GetPosition() + sphere->center_;
	XMVECTOR boxPos = box->pGameObject_->GetPosition() + box->center_;



	if (circlePos.vecX > boxPos.vecX - box->size_.vecX - sphere->size_.vecX &&
		circlePos.vecX < boxPos.vecX + box->size_.vecX + sphere->size_.vecX &&
		circlePos.vecY > boxPos.vecY - box->size_.vecY - sphere->size_.vecX &&
		circlePos.vecY < boxPos.vecY + box->size_.vecY + sphere->size_.vecX &&
		circlePos.vecZ > boxPos.vecZ - box->size_.vecZ - sphere->size_.vecX &&
		circlePos.vecZ < boxPos.vecZ + box->size_.vecZ + sphere->size_.vecX )
	{
		return true;
	}

	return false;
}

//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{

	XMVECTOR Vec = (circleA->center_ + circleA->pGameObject_->GetPosition()) - (circleB->center_ + circleB->pGameObject_->GetPosition());
	Vec = XMVector3Length(Vec);

	if (Vec.vecX <= (circleA->size_.vecX + circleB->size_.vecX))
	{
		return true;
	}

	return false;
}

//テスト表示用の枠を描画
//引数：position	位置
void Collider::Draw(XMVECTOR position)
{
	Transform transform;
	transform.position_ = XMVectorSet(position.vecX + center_.vecX, position.vecY + center_.vecY, position.vecZ + center_.vecZ, 0);
	transform.scale_ = XMVectorSet(size_.vecX, size_.vecY, size_.vecZ, 0.0f);
	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}
