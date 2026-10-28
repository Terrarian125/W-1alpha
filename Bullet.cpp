#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Bullet::Bullet(GameObject * parent)
	:GameObject(parent, "Bullet"), hModel_(-1),
	SPEED(2.0f), GRAVITY(0.000f)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Model/Bullet.fbx");
	assert(hModel_ >= 0);

	//衝突判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.5f);
	AddCollider(collision);
}

//更新
void Bullet::Update()
{
	//移動
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	pos += XMLoadFloat3(&move_);
	XMStoreFloat3(&transform_.position_, pos);

	//重力
	// move_.vecY += dy_;
	// dy_ -= GRAVITY;


	//ある程度低い位置まで落ちたら消す
	//if (transform_.position_.vecY < -5)
	//{
	//	KillMe();
	//}
	if (transform_.position_.z > 30.0f)
	{
		KillMe();
	}
}

//描画
void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Bullet::Release()
{
}


//発射
void Bullet::Shot(XMFLOAT3 position, XMFLOAT3 direction)
{
	//位置
	transform_.position_ = position;

	//移動は、引数で渡された方向にSPEEDの速さ
	XMStoreFloat3(&move_, XMVector3Normalize(XMLoadFloat3(&direction)) * SPEED);

	//重力による落下速度を初期化
	dy_ = 0;
}