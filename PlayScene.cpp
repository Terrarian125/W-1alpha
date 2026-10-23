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

    for (int i = 0; i < ENEMY_NUM; ++i)
        Instantiate<Enemy>(this);

    Instantiate<Infomation>(this);

    text_.Initialize("Fonts/Rye-Regular.ttf", 32.0f);

    const ImVec2 size = ImGui::GetIO().DisplaySize;
    playSceneButton_.Initialize(size.x, size.y, &text_, &timer_);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
    //text_.Draw(32, 32, "Yes!TakasuClinic");

    //ImGui::Begin("PlayScene Debug");
    //ImGui::Text("PlayScene::Draw called");

    //if (startButton != nullptr)
    //{
    //    startButton->Draw();
    //}
    const ImVec2 size = ImGui::GetIO().DisplaySize;
    playSceneButton_.SetScreenSize(size.x, size.y);
    playSceneButton_.Draw();
}

//開放
void PlayScene::Release()
{
    playSceneButton_.Reset();
    text_.Release();
}