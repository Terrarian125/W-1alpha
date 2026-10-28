#include "Cannon.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Bullet.h"

//コンストラクタ
Cannon::Cannon(GameObject * parent)
	:GameObject(parent, "Cannon"), hModel_(-1),
	SWING_SPEED(1.5f)
{
}

//デストラクタ
Cannon::~Cannon()
{
}

//初期化
void Cannon::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Model/TankHead.fbx");
	assert(hModel_ >= 0);
}

//更新
void Cannon::Update()
{
	//右旋回
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += SWING_SPEED;
	}

	//左旋回
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= SWING_SPEED;
	}

	//発射
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//弾をシーンに追加
		GameObject* playScene = FindObject("PlayScene");
		Bullet* pBullet = Instantiate<Bullet>(playScene);

		//砲台の先端と根本の位置を取得
		XMFLOAT3 shotPos = Model::GetBonePosition(hModel_, "ShotPoint");	//先端
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "CannonRoot");	//根本

		//発射方向 = 先端 - 根本
		XMFLOAT3 dir;
		XMStoreFloat3(&dir, XMLoadFloat3(&shotPos) - XMLoadFloat3(&cannonRoot));

		//撃つ
		pBullet->Shot(shotPos, dir);
	}

	//カメラの焦点を砲台に合わせる
	XMVECTOR vTarget = XMVector3TransformCoord(XMLoadFloat3(&transform_.position_), transform_.GetWorldMatrix());
	XMFLOAT3 target;
	XMStoreFloat3(&target, vTarget);
	Camera::SetTarget(target);
}

//描画
void Cannon::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Cannon::Release()
{
}