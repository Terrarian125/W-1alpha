#include "sceneManager.h"

#include "../ChickenRaceScene.h"
#include "../ResultScene.h"

#include "Model.h"
#include "Image.h"
#include "Audio.h"


SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_CHICKEN_RACE_SCENE;
	nextSceneID_ = currentSceneID_;
	Instantiate<ChickenRaceScene>(this);
}

void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_CHICKEN_RACE_SCENE: 
			Instantiate<ChickenRaceScene>(this);
			break;

		case SCENE_ID_RESULT:
			Instantiate<ResultScene>(this);
			break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}