#pragma once
#include "Engine/GameObject.h"

//弾を管理するクラス
class Bullet : public GameObject
{

	int hModel_;		//モデル番号
	XMVECTOR move_;		//移動ベクトル
	float dy_;			//Ｙ方向の加速度

	const float SPEED;		//速度
	const float GRAVITY;	//重力

public:
	//コンストラクタ
	Bullet(GameObject* parent);

	//デストラクタ
	~Bullet();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;


	//発射
	//引数；position	発射位置
	//引数：direction	発射方向
	void Shot(XMVECTOR position, XMVECTOR direction);
};