#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Bullet::Bullet(GameObject * parent)
	:GameObject(parent, "Bullet"), hModel_(-1),
	SPEED(0.3f), GRAVITY(0.001f)
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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider(collision);
}

//更新
void Bullet::Update()
{
	//移動
	transform_.position_.x += move_.x;
	transform_.position_.y += move_.y;
	transform_.position_.z += move_.z;

	//重力
	move_.y += dy_;
	dy_ -= GRAVITY;


	//ある程度低い位置まで落ちたら消す
	if (transform_.position_.y < -5.0f)
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
	XMVECTOR directionVector = XMLoadFloat3(&direction);
	XMVECTOR normalizedDirection = XMVector3Normalize(directionVector);
	XMStoreFloat3(&move_, normalizedDirection * SPEED);
}