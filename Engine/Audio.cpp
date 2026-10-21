#include "Audio.h"

//Sound*	Audio::_pSound = nullptr;

//3D画像を管理する
namespace Audio
{
	//サウンドクラスのオブジェクト
	Sound* _pSound;

	//ロード済みの画像データ一覧
	std::vector<AudioData*>	_datas;


	//初期化
	void Initialize(HWND hWnd)
	{
		_pSound = new Sound;
		_pSound->Initialize(hWnd);
		AllRelease();
	}


	//サウンドファイルをロード
	int Load(std::string fileName)
	{
		AudioData* pData = new AudioData;

		//開いたファイル一覧から同じファイル名のものが無いか探す
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->psoundBuffer = _datas[i]->psoundBuffer;
				isExist = true;
				break;
			}
		}

		//新たにファイルを開く
		if (isExist == false)
		{
			pData->psoundBuffer = new LPDIRECTSOUNDBUFFER;
			if (FAILED(_pSound->Load(pData->psoundBuffer, fileName)))
			{
				//開けなかった
				SAFE_DELETE(pData);
				return -1;
			}

			//無事開けた
			pData->fileName = fileName;
		}


		//使ってない番号が無いか探す
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//新たに追加
		_datas.push_back(pData);
		return (int)_datas.size() - 1;
	}



	//再生
	void Play(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_pSound->Play(_datas[handle]->psoundBuffer);

	}


	//停止
	void Stop(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_pSound->Stop(_datas[handle]->psoundBuffer);
	}



	//任意のサウンドを開放
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		//同じサウンドを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && i != handle && _datas[i]->psoundBuffer == _datas[handle]->psoundBuffer)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->psoundBuffer);
		}


		SAFE_DELETE(_datas[handle]);
	}



	//全てのサウンドを解放
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//ゲーム終了時に行う処理
	void ReleaseDirectSound()
	{
		SAFE_DELETE(_pSound);
	}
}

