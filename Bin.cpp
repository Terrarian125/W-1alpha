#include "Bin.h"
#include "./Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Global.h"

#include <algorithm>
#include <cmath>

#include <imgui.h>

Bin::Bin(GameObject *_pParent) :
	GameObject(_pParent, "Bin"),
	hModel_(-1),
	pouringTime_(),
	isPouring_(false),
	isConfirmed_(false)
{
}

void Bin::Initialize()
{
	hModel_ = Model::Load("Model/bin_mock.fbx");
}

void Bin::Update()
{
	if (not(isConfirmed_))
	{
		if (isPouring_)
		{
			ImGui::Begin("BinRotComp");
			pouringTime_++;
			ImGui::InputInt("pT", &pouringTime_);
			
			isPouring_ = true;
			if (transform_.rotate_.z >= -40)
			{
				float t = std::clamp(pouringTime_ / 50.f, 0.0f, 1.f);
				float c = sinf((t * XM_PI) / 2);
				transform_.rotate_.z = -20.f - 20.f * c;
			
				ImGui::InputFloat("t", &t);
				ImGui::InputFloat("c", &c);
				ImGui::End();
			}
		}
		else
		{
			if (transform_.rotate_.z < -20.f)
			{
				pouringTime_ = 0;
				transform_.rotate_.z = std::lerp(transform_.rotate_.z,
												 -19.f,
												 0.1f);
			}
		}
	}

	isPouring_ = false;

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
	if (not(isConfirmed_))
	{
		isPouring_ = true;
	}
}

void Bin::Conform()
{
	isConfirmed_ = true;
	transform_.rotate_.z = 0;
}
