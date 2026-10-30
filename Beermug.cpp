#include "Beermug.h"
#include "./Engine/Model.h"

#include <imgui.h>

Beermug::Beermug(GameObject *_pParent) :
	GameObject(_pParent, "Beermug"),
	hModels_()
{
}

void Beermug::Initialize()
{
	hModels_[0] = Model::Load("Model/beermug_cross_section_L.fbx");
	hModels_[1] = Model::Load("Model/beermug_cross_section_R.fbx");
}

void Beermug::Update()
{
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

void Beermug::Draw()
{
	Model::SetTransform(hModels_[modelIdx_], transform_);
	Model::Draw(hModels_[modelIdx_]);
}

void Beermug::Release()
{
}
