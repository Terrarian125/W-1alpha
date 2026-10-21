#include "PlayScene.h"
#include "Tank.h"
#include "Ground.h"
#include "Enemy.h"
#include "Infomation.h"
#include "Engine\\FontText.hpp"

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

	text_.Initialize("Fonts/Rye-Regular.ttf", 32.0f);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
	text_.Draw(32, 32, "Yes!TakasuClinic");
}

//開放
void PlayScene::Release()
{
}