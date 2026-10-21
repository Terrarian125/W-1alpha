#pragma once
#include <DirectXMath.h>


#define vecX  m128_f32[0]
#define vecY  m128_f32[1]
#define vecZ  m128_f32[2]


using namespace DirectX;


//-----------------------------------------------------------
//位置、向き、拡大率などを管理するクラス
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列
	XMVECTOR position_;		//位置
	XMVECTOR rotate_;		//向き
	XMVECTOR scale_;		//拡大率
	Transform * pParent_;	//親オブジェクトの情報

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	//引数：なし
	//戻値：なし
	void Calclation();

	//ワールド行列を取得
	//引数：なし
	//戻値：その時点でのワールド行列
	XMMATRIX GetWorldMatrix();
};

