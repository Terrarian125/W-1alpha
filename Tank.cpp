#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Cannon.h"
#include "Ground.h"

#include <DirectXMath.h>
using namespace DirectX;

//コンストラクタ
Tank::Tank(GameObject * parent)
	:GameObject(parent, "Tank"), hModel_(-1), hGroundModel_(-1)
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

	//弾を撃ったときにロードすると処理落ちするので、予めロードしておく
	int hBulletModel;
	hBulletModel = Model::Load("Model/Bullet.fbx");
	assert(hBulletModel >= 0);

	//箱型の当たり判定を作る
	BoxCollider* collision = new BoxCollider(XMVectorSet(0, 0.5f, 0, 0), XMVectorSet(1, 1, 1, 0));
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
	XMMATRIX rotateMatrix = XMMatrixRotationY(transform_.rotate_.vecY / 180 * 3.14f);

	//移動ベクトル
	XMVECTOR  moveVector = XMVector3TransformCoord(XMVectorSet(0, 0, 0.2f, 0), rotateMatrix);



	//前進
	if (Input::IsKey(DIK_W))
	{
		transform_.position_ += moveVector;
	}

	//後退
	if (Input::IsKey(DIK_S))
	{
		transform_.position_ -= moveVector;
	}

	//右旋回
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.vecY += 1;
	}

	//左旋回
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.vecY -= 1;
	}
}

//地面に沿わせる
void Tank::FollowGround()
{

	//まだ地面のモデル番号を知らない
	if (hGroundModel_ == -1)
	{
		//モデル番号を調べる
		hGroundModel_ = ((Ground*)FindObject("Ground"))->GetModelHandle();
	}

	//もう地面のモデル番号を知っている
	else
	{
		//レイを撃つ準備
		RayCastData data;
		data.start = transform_.position_;		//戦車の原点から
		data.start.vecY = 0;						//高さ0（地面は一番高いところでもY<0になっている）
		data.dir = XMVectorSet(0, -1, 0, 0);			//真下方向

														//地面に対してレイを撃つ
		Model::RayCast(hGroundModel_, &data);

		//レイが地面に当たったら
		if (data.hit)
		{
			//戦車の高さを地面にあわせる
			//（Y=0の高さからレイ撃って、data.distメートル先に地面があったということは
			//　そこの標高は『-data.distメートル』ということになる）
			transform_.position_.vecY = -data.dist;
		}
	}
}

//描画
void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Tank::Release()
{
}