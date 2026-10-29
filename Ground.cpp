#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Ground::Ground(GameObject * parent)
	:GameObject(parent, "Ground"), hModel_(-1)
{
	transform_.scale_ = XMFLOAT3(40.0f, 40.0f, 40.0f);
	transform_.rotate_ = XMFLOAT3(0.0f, 180.0f, 0.0f);
}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Model/TestBg00.fbx");
	assert(hModel_ >= 0);
}

//更新
void Ground::Update()
{
}

//描画
void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}


