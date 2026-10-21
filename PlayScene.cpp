#include "PlayScene.h"
#include "Tank.h"
#include "Ground.h"
#include "Enemy.h"
#include "Infomation.h"

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),
	ENEMY_NUM(5)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Tank>(this);
	Instantiate<Ground>(this);

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		Instantiate<Enemy>(this);
	}

	Instantiate<Infomation>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}