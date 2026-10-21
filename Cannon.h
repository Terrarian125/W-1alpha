#pragma once
#include "Engine/GameObject.h"

//戦車の砲台を管理するクラス
class Cannon : public GameObject
{
	const float SWING_SPEED;	//旋回速度

	int hModel_;    //モデル番号

public:
	//コンストラクタ
	Cannon(GameObject* parent);

	//デストラクタ
	~Cannon();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};