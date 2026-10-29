#pragma once
#include "Engine/GameObject.h"

// 銃のレティクルを管理するクラス
class Reticle : public GameObject
{
    // レティクルの座標
    XMFLOAT3 position_;
    XMFLOAT3 rotate_;   // 回転

    // 画像読み込み
    int hImage_;

    // 標準移動
    void Move();

    // 発射
    void Shoot();

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