#pragma once
#include "Engine/GameObject.h"

//戦車（本体）を管理するクラス
class Tank : public GameObject
{
	int hModel_;		//モデル番号
	int hGroundModel_;	//地面のモデル番号


	//移動
	void Move();

	//地面に沿わせる
	void FollowGround();


public:
	//コンストラクタ
	Tank(GameObject* parent);

	//デストラクタ
	~Tank();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;


	//描画
	void Draw() override;

	//開放
	void Release() override;
};