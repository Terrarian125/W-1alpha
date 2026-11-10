#pragma once
#include "Engine/GameObject.h"
#include "Engine/FontText.hpp"

// クレーを管理するクラス
class Clay : public GameObject
{
    FontText textClay_;       //テキスト描画用のオブジェクト

    // クレーの座標
    XMFLOAT3 position_[10]; // 位置
    XMFLOAT3 rotate_[10];   // 回転
    XMFLOAT3 scale_[10];    // 拡大率

    int hModel_[10];     //モデル番号
    //int hImage_;      // 画像読み込み

    int ClayNum_;

    //移動
    void Move();

    bool OnDown_[10]; // 下がるか上がるかのフラグ　    ※ true：下がる / false：上がる
    bool IsDead_[10]; // クレーの死亡しているかフラグ　※ true：死亡 / false：生存

    const float HitRange = 0.5f; // 当たり判定の大きさ

    int Score_[10];            // 各クレーごとにスコア
    static int TotalScore_[2]; // 合計のスコア

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
    //void OnCollision(GameObject* pTarget) override;

    // レティクルの中心がクレーに重なっているかの確認処理
    int FindOverlap_1P(const XMFLOAT2& reticleNdc_1P) const;
    int FindOverlap_2P(const XMFLOAT2& reticleNdc_2P) const;

    // 発砲時、レティクルが重なっているクレーがあれば壊す
    bool TryBreak_1P(const XMFLOAT2& reticleNdc_1P);
    bool TryBreak_2P(const XMFLOAT2& reticleNdc_2P);

    // 合計スコアを取得
    static int GetTotalScore_1P() { return TotalScore_[0]; }
    static int GetTotalScore_2P() { return TotalScore_[1]; }

    // 合計スコアをリセット
    static void ScoreReset() { TotalScore_[0] = 0, TotalScore_[1] = 0; }

};