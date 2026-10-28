#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Cannon.h"
#include "Ground.h"
#include "Engine/Image.h"

#include <DirectXMath.h>
using namespace DirectX;

//コンストラクタ
Tank::Tank(GameObject * parent)
	:GameObject(parent, "Tank"), hModel_(-1), hGroundModel_(-1)//, hImage_(-1)
{
}

//デストラクタ
Tank::~Tank()
{
}

//初期化
void Tank::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("/Model/TankBody.fbx");
	assert(hModel_ >= 0);

	//子供として砲台を作成
	Instantiate<Cannon>(this);

	//画像データのロード
	//hImage_ = Image::Load("Image/UI1.png");
	//assert(hImage_ >= 0);

	//弾を撃ったときにロードすると処理落ちするので、予めロードしておく
	int hBulletModel;
	hBulletModel = Model::Load("Model/Bullet.fbx");
	assert(hBulletModel >= 0);

	//箱型の当たり判定を作る
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.5f, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);
}

//更新
void Tank::Update()
{
	//移動
	Move();

	//地面に沿わせる
	FollowGround();

	//敵がもういなかったらクリア画面へ
	if (FindObject("Enemy") == nullptr)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}

//移動
void Tank::Move()
{
	//戦車が向いている方向に回転させる行列
	XMMATRIX rotateMatrix = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//移動ベクトル
	XMVECTOR moveVector = XMVector3TransformCoord(XMVectorSet(0, 0, 0.2f, 0), rotateMatrix);

	//現在位置をXMVECTORに変換して計算
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);

	//前進
	if (Input::IsKey(DIK_W))
	{
		pos += moveVector;
	}

	//後退
	if (Input::IsKey(DIK_S))
	{
		pos -= moveVector;
	}

	//計算結果を戻す
	XMStoreFloat3(&transform_.position_, pos);

	//右旋回
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1;
	}

	//左旋回
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1;
	}
}

//地面に沿わせる
void Tank::FollowGround()
{
	//まだ地面のモデル番号を知らない
	if (hGroundModel_ == -1)
	{
		hGroundModel_ = ((Ground*)FindObject("Ground"))->GetModelHandle();
	}

	//もう地面のモデル番号を知っている
	else
	{
		//レイを撃つ準備
		RayCastData data;
		data.start = transform_.position_;		//戦車の原点から
		data.start.y = 0;						//高さ0（地面は一番高いところでもY<0）
		data.dir = XMFLOAT3(0, -1, 0);			//真下方向

		//地面に対してレイを撃つ
		Model::RayCast(hGroundModel_, &data);

		//レイが地面に当たったら
		if (data.hit)
		{
			transform_.position_.y = -data.dist;
		}
	}
}

//描画
void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//Image::SetTransform(hImage_, transform_);
	//Image::Draw(hImage_);
}

//開放
void Tank::Release()
{
}