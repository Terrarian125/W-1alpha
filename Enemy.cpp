#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/SceneManager.h"
#include "Ground.h"

//コンストラクタ
Enemy::Enemy(GameObject * parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hSound_(-1)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Model/Enemy.fbx");
	assert(hModel_ >= 0);


	//アニメーションの設定
	Model::SetAnimFrame(hModel_, 0, 300, 2.0f);


	//サイズ
	transform_.scale_ = XMVectorSet(2.0f, 2.0f, 2.0f, 0);


	//位置
	transform_.position_.vecX = (float)(rand() % 100 - 50);
	transform_.position_.vecZ = (float)(rand() % 100 - 50);


	//地面の高さ
	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMVectorSet(0, -1, 0, 0);
	int hGroundModel = ((Ground*)FindObject("Ground"))->GetModelHandle();
	Model::RayCast(hGroundModel, &data);
	transform_.position_.vecY = -data.dist;


	//向き
	transform_.rotate_.vecY = (float)(rand() % 360);


	//当たり判定追加
	SphereCollider* collision = new SphereCollider(XMVectorSet(0, 0.7f, 0, 0), 2.0f);
	AddCollider(collision);


	//サウンドデータのロード
	hSound_ = Audio::Load("Audio/Explode.wav");
	assert(hSound_ >= 0);
}

//更新
void Enemy::Update()
{
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}



//何かに当たった
void Enemy::OnCollision(GameObject * pTarget)
{
	//弾に当たった
	if (pTarget->GetObjectName() == "Bullet")
	{
		//自分を消す
		KillMe();

		//相手（弾）を消す
		pTarget->KillMe();

		//効果音を鳴らす
		Audio::Play(hSound_);
	}


	//プレイヤー（戦車）に当たった
	if (pTarget->GetObjectName() == "Tank")
	{
		//ゲームオーバーシーンへ
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}