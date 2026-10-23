#include "FontText.hpp"
#include "../ImGui/imgui.h"

HRESULT FontText::Initialize(const char* fileName, float fontSize)
{
	Release();
	if (!fileName || fileName[0] == '\0' || fontSize <= 0.0f || !ImGui::GetCurrentContext())
		return E_INVALIDARG;

	font_ = ImGui::GetIO().Fonts->AddFontFromFileTTF(
		fileName,
		fontSize,
		nullptr,
		ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
	if (!font_)
		return E_FAIL;

	fontSize_ = fontSize;
	return S_OK;
}

void FontText::Draw(float x, float y, const char* text, unsigned int color) const
{
	if (!font_ || !text || !ImGui::GetCurrentContext())
		return;

	ImGui::GetForegroundDrawList()->AddText(
		font_, fontSize_, ImVec2(x, y), static_cast<ImU32>(color), text);
}

void FontText::Release()
{
	font_ = nullptr;
	fontSize_ = 24.0f;
}
