#include "Bin.h"
#include "./Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Global.h"

#include <algorithm>
#include <cmath>

#include <imgui.h>

namespace
{
	bool isConfirmed{false};
	int  pouringTime{0};
}

Bin::Bin(GameObject *_pParent) :
	GameObject(_pParent, "Bin"),
	hModel_(-1),
	isPouring_(false)
{
}

void Bin::Initialize()
{
	hModel_ = Model::Load("Model/bin_mock.fbx");
}

void Bin::Update()
{
	// 初期状態に戻す
	if (transform_.rotate_.z <= -20.f and isPouring_)
	{
		isPouring_  = false;
		pouringTime = 0;
		transform_.rotate_.z = std::lerp(transform_.rotate_.z,
										 -20.f,
										 0.1f);
	}

	if (not(isConfirmed))
	{
		// オーバ時の修正
		if (transform_.rotate_.z < -20.0f)
		{
			transform_.rotate_.z += 3;
		}
		else
		{
			transform_.rotate_.z = -20.0f;
		}
	}


#ifdef _DEBUG
	std::string panelName{ "ObjectTS" + objectName_ };

	ImGui::Begin(panelName.c_str());
	ImGui::InputFloat("pos.x", &transform_.position_.x);
	ImGui::InputFloat("pos.y", &transform_.position_.y);
	ImGui::InputFloat("pos.z", &transform_.position_.z);

	ImGui::InputFloat("rot.x", &transform_.rotate_.x);
	ImGui::InputFloat("rot.y", &transform_.rotate_.y);
	ImGui::InputFloat("rot.z", &transform_.rotate_.z);

	ImGui::InputFloat("scl.x", &transform_.scale_.x);
	ImGui::InputFloat("scl.y", &transform_.scale_.y);
	ImGui::InputFloat("scl.z", &transform_.scale_.z);
	ImGui::End();
#endif
}

void Bin::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bin::Release()
{}

void Bin::Pouring()
{
	if (not(isConfirmed))
	{
		pouringTime++;
		isPouring_ = true;
		if (transform_.rotate_.z >= -40)
		{
			float t = std::clamp(pouringTime / 60.f, 0.0f, 1.0f);
			transform_.rotate_.z = -20.f - 20.f * sinf(t * XM_PIDIV2);
		}
	}
}

void Bin::Conform()
{
	isConfirmed = true;
	transform_.rotate_.z = 0;
}
