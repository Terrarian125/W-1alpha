#pragma once
#include "Engine/GameObject.h"

//銃を管理するクラス
class Gun : public GameObject
{
    // 座標
    XMFLOAT3 position_;

    int hModel_;        // モデル番号
    //int hImage_;      // 画像読み込み

    //移動
    void Move();

public:
    //コンストラクタ
    Gun(GameObject* parent);

    //デストラクタ
    ~Gun();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};