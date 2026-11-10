#include "ClearScene.h"
#include "Engine/Image.h"
#include "Engine\\FontText.hpp"

#include "Clay.h"

//コンストラクタ
ClearScene::ClearScene(GameObject * parent)
	: GameObject(parent, "ClearScene"), hPict_{ -1,-1,-1 }
{
}

//初期化
void ClearScene::Initialize()
{
	//画像データのロード
	hPict_[0] = Image::Load("Image/BG.jpg");
	assert(hPict_[0] >= 0);
	Image::SetRect(hPict_[0], 0, 0, 1280, 720);

	hPict_[1] = Image::Load("Image/Reticle_1P.png");
	assert(hPict_[1] >= 0);
	hPict_[2] = Image::Load("Image/Reticle_2P.png");
	assert(hPict_[2] >= 0);

	// 一応あると楽だからここに
	position_[1] = { -0.5f, 0.3f, 0.0f }; // 位置
	scale_[1]    = {  0.5f, 0.5f, 0.0f }; // 拡大率

	position_[2] = {  0.5f, 0.3f,  0.0f }; // 位置
	scale_[2]    = {  0.5f, 0.5f,  0.0f }; // 拡大率

	//textWin_.Initialize("Fonts/Rye-Regular.ttf", 28.0f);
}

//更新
void ClearScene::Update()
{
}

//描画
void ClearScene::Draw()
{

	// レティクル表示
	Image::Draw(hPict_[0]);

	if (Clay::GetTotalScore_1P() > Clay::GetTotalScore_2P()) {
		transform_.position_ = { position_[1].x,position_[1].y,position_[1].z };  // 位置
		transform_.scale_ = { scale_[1].x, scale_[1].y, scale_[1].z };          // 拡大率
		Image::SetTransform(hPict_[1], transform_);
		Image::Draw(hPict_[1]);
	}
	else if (Clay::GetTotalScore_1P() < Clay::GetTotalScore_2P()) {
		transform_.position_ = { position_[2].x,position_[2].y,position_[2].z };  // 位置
		transform_.scale_ = { scale_[2].x, scale_[2].y, scale_[2].z };          // 拡大率
		Image::SetTransform(hPict_[2], transform_);
		Image::Draw(hPict_[2]);
	}
	else {
		transform_.position_ = { position_[1].x,position_[1].y,position_[1].z };  // 位置
		transform_.scale_ = { scale_[1].x, scale_[1].y, scale_[1].z };          // 拡大率
		Image::SetTransform(hPict_[1], transform_);
		Image::Draw(hPict_[1]);

		transform_.position_ = { position_[2].x,position_[2].y,position_[2].z };  // 位置
		transform_.scale_ = { scale_[2].x, scale_[2].y, scale_[2].z };          // 拡大率
		Image::SetTransform(hPict_[2], transform_);
		Image::Draw(hPict_[2]);
	}

	//textWin_.Draw(32, 32, "Clay shooting");
}

//開放
void ClearScene::Release()
{
}