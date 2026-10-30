#pragma once
#include "Engine/GameObject.h"

// クレーを管理するクラス
class Clay : public GameObject
{
    // クレーの座標
    XMFLOAT3 position_[3]; // 位置
    XMFLOAT3 rotate_[3];   // 回転
    XMFLOAT3 scale_[3];    // 拡大率

    int hModel_[3];     //モデル番号
    //int hImage_;      // 画像読み込み

    //移動
    void Move();

    bool On_down[3]; // 下がるか上がるかのフラグ　※ true：下がる / false：上がる

public:
    //コンストラクタ
    Clay(GameObject* parent);

    //デストラクタ
    ~Clay();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;


    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget　当たった相手
    void OnCollision(GameObject* pTarget) override;
};