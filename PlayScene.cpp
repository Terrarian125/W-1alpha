#include "PlayScene.h"
#include "Tank.h"
#include "Ground.h"
#include "Enemy.h"
#include "Infomation.h"
#include "Engine\\FontText.hpp"
#include "Engine\\GUIbutton.h"
#include <Imgui.h>

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

    // ボタンを生成（位置X、位置Y、幅、高さ、表示文字）
    startButton = new GuiButton(
        100,  // X座標
        100,  // Y座標
        200,  // 幅
        60,   // 高さ
        "ゲームスタート"
    );
    // クリックされたときの処理
    startButton->onClick = [this]()
        {
        };

    // 説明文
    startButton->SetDescription("クリックしてゲームを開始します");
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
    text_.Draw(32, 32, "Yes!TakasuClinic");

    ImGui::Begin("PlayScene Debug");
    ImGui::Text("PlayScene::Draw called");

    if (startButton != nullptr)
    {
        ImGui::Text("startButton is not null");
        startButton->Draw();
    }
    else
    {
        ImGui::Text("startButton is null");
    }

    ImGui::End();
}

//開放
void PlayScene::Release()
{
    delete startButton;
    startButton = nullptr;
}