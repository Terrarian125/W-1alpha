#pragma once

#pragma once

#include <vector>
#include <string>
#include "Global.h"
#include "Sound.h"


//-----------------------------------------------------------
//効果音を管理する
//-----------------------------------------------------------
namespace Audio
{
	//ひとつのサウンドの情報
	struct AudioData
	{
		//ファイル名
		std::string fileName;

		//サウンドバッファ（読み込んだサウンドを入れる）
		LPDIRECTSOUNDBUFFER* 	psoundBuffer;


		//コンストラクタ
		AudioData() :psoundBuffer(nullptr)
		{
		}

	};



	//初期化
	//引数：hWnd	ウィンドウハンドル
	void Initialize(HWND hWnd);


	//サウンドファイルをロード
	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	//引数：fileName　ファイル名
	//戻値：そのサウンドデータに割り当てられた番号
	int Load(std::string fileName);

	//再生
	//引数：handle	再生したいサウンドの番号
	void Play(int handle);

	//停止
	//引数：handle	止めたいサウンドの番号
	void Stop(int handle);

	//任意のサウンドを開放
	//引数：handle	開放したいサウンドの番号
	void Release(int handle);

	//全てのサウンドを解放
	//（シーンが切り替わるときは必ず実行）
	void AllRelease();

	//ゲーム終了時に行う処理
	void ReleaseDirectSound();
}