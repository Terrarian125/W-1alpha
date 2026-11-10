#pragma once
#include "Engine/GameObject.h"
#include "Engine/FontText.hpp"

// 銃のレティクルを管理するクラス
class Reticle : public GameObject
{
    FontText textReticle_;       //テキスト描画用のオブジェクト

    // レティクルの座標
    XMFLOAT3 position_[2];
    XMFLOAT3 rotate_;   // 回転
    XMFLOAT3 scale_;

    // 画像読み込み
    int hImage_;

    // 標準移動
    void Move();

    // 発射
    void Shoot_1P();
    void Shoot_2P();

    bool triggerOld_[2] = { false, false };

public:
    // コンストラクタ
    Reticle(GameObject* parent);

    // デストラクタ
    ~Reticle();

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 開放
    void Release() override;
};