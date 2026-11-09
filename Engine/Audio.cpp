#include <Windows.h>
#include <xaudio2.h>
#include <mfapi.h>
#include <mfobjects.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <wrl/client.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include "Audio.h"

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "ole32.lib")

using Microsoft::WRL::ComPtr;

namespace Audio
{
    namespace
    {
        //XAudio本体
        IXAudio2* pXAudio = nullptr;

        //マスターボイス
        IXAudio2MasteringVoice* pMasteringVoice = nullptr;

        //ファイル毎に必要な情報
        struct AudioData
        {
            //サウンド情報
            XAUDIO2_BUFFER buf = {};

            //デコードしたPCMデータ
            std::vector<BYTE> pcmData;

            //PCMデータのフォーマット
            std::vector<BYTE> waveFormat;

            //ソースボイス
            std::vector<IXAudio2SourceVoice*> sourceVoices;

            //ファイル名
            std::string fileName;
        };
        std::vector<AudioData> audioDatas;

        bool comReady = false;
        bool ownsComInitialization = false;
        bool mediaFoundationStarted = false;

        //Media FoundationでWAV/MP3をPCMへデコードする。
        HRESULT DecodeToPcm(const std::string& fileName, AudioData& audio)
        {
            //Media Foundationへ渡すため、ファイル名をワイド文字列へ変換する。
            const int wideLength = MultiByteToWideChar(
                CP_ACP, 0, fileName.c_str(), -1, nullptr, 0);
            if (wideLength <= 1)
                return E_INVALIDARG;

            std::wstring path(static_cast<size_t>(wideLength), L'\0');
            if (MultiByteToWideChar(
                CP_ACP, 0, fileName.c_str(), -1, path.data(), wideLength) == 0)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }
            path.resize(static_cast<size_t>(wideLength - 1));

            //相対パスでもSource Readerが開けるよう、絶対パスにする。
            const DWORD fullPathLength = GetFullPathNameW(path.c_str(), 0, nullptr, nullptr);
            if (fullPathLength == 0)
                return HRESULT_FROM_WIN32(GetLastError());

            std::wstring fullPath(static_cast<size_t>(fullPathLength), L'\0');
            const DWORD written = GetFullPathNameW(
                path.c_str(), fullPathLength, fullPath.data(), nullptr);
            if (written == 0 || written >= fullPathLength)
                return HRESULT_FROM_WIN32(GetLastError());
            fullPath.resize(written);

            //ファイルの音声ストリームを読むSource Readerを作成する。
            ComPtr<IMFSourceReader> reader;
            HRESULT hr = MFCreateSourceReaderFromURL(
                fullPath.c_str(), nullptr, reader.GetAddressOf());
            if (FAILED(hr))
                return hr;

            //XAudio2で扱える16-bit PCMを出力形式に指定する。
            ComPtr<IMFMediaType> outputType;
            hr = MFCreateMediaType(outputType.GetAddressOf());
            if (FAILED(hr))
                return hr;

            hr = outputType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
            if (SUCCEEDED(hr))
                hr = outputType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
            if (SUCCEEDED(hr))
                hr = outputType->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
            if (FAILED(hr))
                return hr;

            hr = reader->SetCurrentMediaType(
                MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, outputType.Get());
            if (FAILED(hr))
                return hr;

            //実際に設定されたPCM形式を取得する。
            ComPtr<IMFMediaType> currentType;
            hr = reader->GetCurrentMediaType(
                MF_SOURCE_READER_FIRST_AUDIO_STREAM, currentType.GetAddressOf());
            if (FAILED(hr))
                return hr;

            //XAudio2用のWAVEFORMATEXを作り、AudioData内で保持する。
            WAVEFORMATEX* waveFormat = nullptr;
            UINT32 waveFormatSize = 0;
            hr = MFCreateWaveFormatExFromMFMediaType(
                currentType.Get(), &waveFormat, &waveFormatSize,
                MFWaveFormatExConvertFlag_Normal);
            if (FAILED(hr))
                return hr;

            if (waveFormatSize < sizeof(WAVEFORMATEX))
            {
                CoTaskMemFree(waveFormat);
                return E_FAIL;
            }
            audio.waveFormat.resize(waveFormatSize);
            std::memcpy(audio.waveFormat.data(), waveFormat, waveFormatSize);
            CoTaskMemFree(waveFormat);

            //サンプルを最後まで読み、PCMデータを連結する。
            for (;;)
            {
                DWORD actualStream = 0;
                DWORD streamFlags = 0;
                LONGLONG timestamp = 0;
                ComPtr<IMFSample> sample;
                hr = reader->ReadSample(
                    MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, &actualStream,
                    &streamFlags, &timestamp, sample.GetAddressOf());
                if (FAILED(hr))
                    return hr;

                if (sample)
                {
                    ComPtr<IMFMediaBuffer> mediaBuffer;
                    hr = sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());
                    if (FAILED(hr))
                        return hr;

                    BYTE* data = nullptr;
                    DWORD currentLength = 0;
                    hr = mediaBuffer->Lock(&data, nullptr, &currentLength);
                    if (FAILED(hr))
                        return hr;

                    if (currentLength > 0)
                        audio.pcmData.insert(audio.pcmData.end(), data, data + currentLength);
                    mediaBuffer->Unlock();
                }

                if ((streamFlags & MF_SOURCE_READERF_ENDOFSTREAM) != 0)
                    break;
            }

            if (audio.pcmData.empty() || audio.pcmData.size() > UINT32_MAX)
                return E_FAIL;

            return S_OK;
        }
    }

    //初期化
    void Initialize()
    {
        //COMは一度だけ初期化する。シーン切り替え時の再呼び出しにも対応する。
        if (!comReady)
        {
            const HRESULT comResult = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
            if (SUCCEEDED(comResult))
            {
                comReady = true;
                ownsComInitialization = true;
            }
            else if (comResult == RPC_E_CHANGED_MODE)
            {
                comReady = true;
            }
        }

        //Media Foundationを開始する。
        if (comReady && !mediaFoundationStarted)
            mediaFoundationStarted = SUCCEEDED(MFStartup(MF_VERSION, MFSTARTUP_FULL));

        //XAudio本体とマスターボイスを作成する。
        if (!pXAudio && SUCCEEDED(XAudio2Create(&pXAudio)))
            pXAudio->CreateMasteringVoice(&pMasteringVoice);
        else if (pXAudio && !pMasteringVoice)
            pXAudio->CreateMasteringVoice(&pMasteringVoice);
    }

    //サウンドファイル（WAV/MP3）をロード
    int Load(std::string fileName, bool isLoop, int svNum)
    {
        //すでに同じファイルを使っていないかチェックする。
        for (size_t i = 0; i < audioDatas.size(); ++i)
        {
            if (audioDatas[i].fileName == fileName)
                return static_cast<int>(i);
        }

        if (!mediaFoundationStarted || !pXAudio || !pMasteringVoice || svNum <= 0)
            return -1;

        AudioData audio;
        audio.fileName = fileName;
        if (FAILED(DecodeToPcm(fileName, audio)))
            return -1;

        //PCM形式をXAudio2に渡してソースボイスを作成する。
        const auto* format = reinterpret_cast<const WAVEFORMATEX*>(audio.waveFormat.data());
        audio.sourceVoices.resize(static_cast<size_t>(svNum), nullptr);
        for (IXAudio2SourceVoice*& sourceVoice : audio.sourceVoices)
        {
            if (FAILED(pXAudio->CreateSourceVoice(&sourceVoice, format)))
            {
                for (IXAudio2SourceVoice* createdVoice : audio.sourceVoices)
                {
                    if (createdVoice)
                        createdVoice->DestroyVoice();
                }
                return -1;
            }
        }

        audio.buf.Flags = XAUDIO2_END_OF_STREAM;
        audio.buf.AudioBytes = static_cast<UINT32>(audio.pcmData.size());
        audio.buf.LoopCount = isLoop ? XAUDIO2_LOOP_INFINITE : 0;

        audioDatas.push_back(std::move(audio));
        AudioData& storedAudio = audioDatas.back();
        storedAudio.buf.pAudioData = storedAudio.pcmData.data();
        return static_cast<int>(audioDatas.size() - 1);
    }

    //再生
    void Play(int ID)
    {
        if (ID < 0 || static_cast<size_t>(ID) >= audioDatas.size())
            return;

        AudioData& audio = audioDatas[static_cast<size_t>(ID)];
        for (IXAudio2SourceVoice* sourceVoice : audio.sourceVoices)
        {
            XAUDIO2_VOICE_STATE state = {};
            sourceVoice->GetState(&state);

            if (state.BuffersQueued == 0)
            {
                if (SUCCEEDED(sourceVoice->SubmitSourceBuffer(&audio.buf)))
                    sourceVoice->Start();
                break;
            }
        }
    }

    //停止
    void Stop(int ID)
    {
        if (ID < 0 || static_cast<size_t>(ID) >= audioDatas.size())
            return;

        for (IXAudio2SourceVoice* sourceVoice : audioDatas[static_cast<size_t>(ID)].sourceVoices)
        {
            sourceVoice->Stop();
            sourceVoice->FlushSourceBuffers();
        }
    }

    //シーンごとの解放
    void Release()
    {
        for (AudioData& audio : audioDatas)
        {
            for (IXAudio2SourceVoice* sourceVoice : audio.sourceVoices)
            {
                if (sourceVoice)
                    sourceVoice->DestroyVoice();
            }
        }
        audioDatas.clear();
    }

    //本体の解放
    void AllRelease()
    {
        Release();

        if (pMasteringVoice)
        {
            pMasteringVoice->DestroyVoice();
            pMasteringVoice = nullptr;
        }
        if (pXAudio)
        {
            pXAudio->Release();
            pXAudio = nullptr;
        }
        if (mediaFoundationStarted)
        {
            MFShutdown();
            mediaFoundationStarted = false;
        }
        if (ownsComInitialization)
        {
            CoUninitialize();
            ownsComInitialization = false;
        }
        comReady = false;
    }
}