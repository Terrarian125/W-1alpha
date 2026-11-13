#include "Horse.hpp"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include <imgui.h>

Horse::Horse(GameObject* parent)
	:GameObject(parent, "Horse"), hModel_(-1), speed_(0.0f), jumpPower_(600.0f), 
	velocity_(-9.8f), gravity_(-980.0f), isGround_(true), isHit_(false)
{
}

void Horse::Initialize()
{
	hModel_ = Model::Load("Model/Horse00.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = XMFLOAT3(0, 0, 0);

	speed_ = 0.5f;

	knockbackVelocity_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
	knockbackTime_ = 0.0f;

	XMFLOAT3 centerPos = { 0, 75, 0 };
	colPos_ = centerPos;
	AddCollider(new BoxCollider(colPos_, { 100, 100, 150 }));
}

void Horse::Update()
{
	static float dt;
	dt += deltaTime;

	if (knockbackTime_ > 0.0f)
	{
		NockBack();
	}
	else
	{
		Run();

		Jump();

		// 左右移動
		if (transform_.position_.x < -400.0f)
		{
			transform_.position_.x = -400.0f;
		}
		else if (transform_.position_.x > 400.0f)
		{
			transform_.position_.x = 400.0f;
		}
		if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_LEFT) || Input::IsKey(DIK_LEFT))
		{
			transform_.position_.x -= 5.0f;
			transform_.rotate_.y = -15.0f;
		}
		else if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_RIGHT) || Input::IsKey(DIK_RIGHT))
		{
			transform_.position_.x += 5.0f;
			transform_.rotate_.y = 15.0f;
		}
		else
		{
			transform_.rotate_.y = 0.0f;
		}
	}

	constexpr float upPosition = 500.0f;
	constexpr float backPosition = -500.0f;
	Camera::SetPosition(XMFLOAT3(500, upPosition, transform_.position_.z + backPosition));
	

	float targetPositionX = 0;
	float targetPositionY = 200.0f;
	float targetPositionZ = transform_.position_.z + 100.0f;
	Camera::SetTarget(XMFLOAT3(targetPositionX, targetPositionY, targetPositionZ));

	ImGui::Begin("Horse Info");
	ImGui::InputFloat("Position X", &transform_.position_.x);
	ImGui::InputFloat("Position Y", &transform_.position_.y);
	ImGui::InputFloat("Position Z", &transform_.position_.z);
	ImGui::InputFloat("delta",&deltaTime);
	ImGui::InputFloat("Speed", &speed_);
	ImGui::Text("Is Hit: %s", isHit_ ? "true" : "false");
	ImGui::End();

	ImGui::Begin("Time Info");
	ImGui::InputFloat("Time", &dt);
	ImGui::End();
}


void Horse::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	CollisionDraw();
}

void Horse::Release()
{
}

void Horse::Run()
{
	transform_.position_.z += speed_;

	if (speed_ < 15.0f)
	{
		speed_ += 0.1f;
	}
}

void Horse::Jump()
{
	// ジャンプ
	if ((Input::IsPadButtonDown(0, XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_SPACE)) && isGround_)
	{
		velocity_ = jumpPower_;
		isGround_ = false;
	}
	// 重力
	velocity_ += gravity_ * deltaTime;

	// 座標更新
	transform_.position_.y += velocity_ * deltaTime;

	// 着地判定
	if (transform_.position_.y <= 0.0f)
	{
		transform_.position_.y = 0.0f;
		velocity_ = 0.0f;
		isGround_ = true;
	}
}

void Horse::NockBack()
{
	if (knockbackTime_ > 0.0f)
	{
		transform_.position_.x += knockbackVelocity_.x * deltaTime;
		transform_.position_.z += knockbackVelocity_.z * deltaTime;

		knockbackTime_ -= deltaTime;

		return; // 通常移動を行わない
	}
}

void Horse::OnCollision(GameObject* pTarget)
{
	OutputDebugStringA("Horse OnCollision!!\n");

	if (pTarget == nullptr) return;

	// ノックバック中なら再設定しない
	if (knockbackTime_ > 0.0f) return;

	XMFLOAT3 playerPos = GetWorldPosition();
	XMFLOAT3 targetPos = pTarget->GetWorldPosition();

	// 障害物から離れる方向
	XMFLOAT3 dir;
	dir.x = playerPos.x - targetPos.x;
	dir.y = 0.0f;
	dir.z = playerPos.z - targetPos.z;

	float length = sqrtf(dir.x * dir.x + dir.z * dir.z);

	if (length > 0.001f)
	{
		dir.x /= length;
		dir.z /= length;
	}
	else
	{
		// 中心が完全に重なった場合の仮方向
		dir.x = 0.0f;
		dir.z = -1.0f;
	}

	float power = 500.0f;

	knockbackVelocity_.x = dir.x * power;
	knockbackVelocity_.y = 0.0f;
	knockbackVelocity_.z = dir.z * power;

	knockbackTime_ = 0.5f;

	speed_ = 0.5f;
}
