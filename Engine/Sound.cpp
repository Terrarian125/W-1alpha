#include<assert.h>
#include "Sound.h"


//コンストラクタ
Sound::Sound() :
	pDSound_(nullptr),
	pPrimary_(nullptr)
{
}


//デストラクタ
Sound::~Sound()
{
	Release();
}

//初期化
void Sound::Initialize(HWND hWnd)
{
	HRESULT ret;

	// COMの初期化
	CoInitialize(NULL);

	// DirectSound8を作成
	ret = DirectSoundCreate8(NULL, &pDSound_, NULL);
	assert(SUCCEEDED(ret));


	// 強調モード
	ret = pDSound_->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	assert(SUCCEEDED(ret));

	//プライマリサウンドバッファの作成
	CreatePrimaryBuffer();
}



//プライマリサウンドバッファの作成
void Sound::CreatePrimaryBuffer()
{
	HRESULT ret;
	WAVEFORMATEX wf;

	// プライマリサウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;
	ret = pDSound_->CreateSoundBuffer(&dsdesc, &pPrimary_, NULL);
	assert(SUCCEEDED(ret));

	// プライマリバッファのステータスを決定
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	ret = pPrimary_->SetFormat(&wf);
	assert(SUCCEEDED(ret));
}


//ファイルのロード
HRESULT Sound::Load(LPDIRECTSOUNDBUFFER * dsb, std::string file)
{
	HRESULT ret;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf;

	// WAVファイルをロード
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file.c_str(), NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc)
	{
		return E_FAIL;
	}

	// 'WAVE'チャンクチェック
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	assert(mSrcWaveFile.fccType == mmioFOURCC('W', 'A', 'V', 'E'));

	// 'fmt 'チャンクチェック
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	assert(mSrcWaveFmt.ckid == mmioFOURCC('f', 'm', 't', ' '));

	// ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// ヘッダメモリ確保
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	assert(wf);
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVEフォーマットのロード
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	assert(SUCCEEDED(ret));


	// fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// dataチャンクを探す
	while (1) {
		// 検索
		ret = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
		assert(SUCCEEDED(ret));

		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// 次のチャンクへ
		ret = mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	// サウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = pDSound_->CreateSoundBuffer(&dsdesc, dsb, NULL);
	assert(SUCCEEDED(ret));

	// ロック開始
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	assert(SUCCEEDED(ret));

	// データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ロック解除
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// ヘッダ用メモリを開放
	free(wf);

	// WAVを閉じる
	mmioClose(hSrc, 0);

	return S_OK;

}

//再生
void Sound::Play(LPDIRECTSOUNDBUFFER* dsb)
{
	(*dsb)->SetCurrentPosition(0);
	(*dsb)->Play(0, 0, 0);

}

//停止
void Sound::Stop(LPDIRECTSOUNDBUFFER* dsb)
{
	(*dsb)->Stop();
}

//開放
void Sound::Release()
{
	pPrimary_->Release();
	pDSound_->Release();

	// COMの終了
	CoUninitialize();
}
