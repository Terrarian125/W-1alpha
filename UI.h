#pragma once
#include "Engine/GameObject.h"
#include "Engine/FontText.hpp"

// UIを管理するクラス
class UI : public GameObject
{
    FontText textB_num_;    //テキスト描画用のオブジェクト
    FontText textTimer_;    //テキスト描画用のオブジェクト
    FontText textScore_;    //テキスト描画用のオブジェクト

    // UIの座標
    XMFLOAT3 position_[2]; // 位置
    XMFLOAT3 rotate_[2];   // 回転
    XMFLOAT3 scale_[2];    // 拡大率

    // 画像読み込み
    int hImage_[2];

    int Bullet_num;   // 残弾数
    int Score;        // スコア
    float Game_Timer; // 試合時間

    bool triggerOld_ = false;

public:
    // コンストラクタ
    UI(GameObject* parent);

    // デストラクタ
    ~UI();

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 開放
    void Release() override;
};