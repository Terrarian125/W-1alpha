#include "PlaySceneButton.h"

#include <imgui.h>
#include <algorithm>
#include <cstdio>
#include <random>

bool PlaySceneButton::Initialize(
    float screenWidth, float screenHeight, FontText* font, GameTimer* timer)
{
    if (!font || !timer)
        return false;

    font_ = font;
    timer_ = timer;
    SetScreenSize(screenWidth, screenHeight);

    startButton_.reset(new GuiButton(0, 0, 180, 56, "START"));
    leftStopButton_.reset(new GuiButton(0, 0, 180, 56, "STOP"));
    rightStopButton_.reset(new GuiButton(0, 0, 180, 56, "STOP"));

    startButton_->SetDescription("");
    leftStopButton_->SetDescription("L Stop");
    rightStopButton_->SetDescription("R Stop");

    startButton_->onClick = [this]() { OnStartClicked(); };
    leftStopButton_->onClick = [this]() { OnStopClicked(-1); };
    rightStopButton_->onClick = [this]() { OnStopClicked(1); };

    UpdateButtonPositions();
    Reset();
    return true;
}

void PlaySceneButton::SetScreenSize(float screenWidth, float screenHeight)
{
    screenWidth_ = (std::max)(1.0f, screenWidth);
    screenHeight_ = (std::max)(1.0f, screenHeight);
    UpdateButtonPositions();
}

void PlaySceneButton::UpdateButtonPositions()
{
    const int buttonWidth = 180;
    const int buttonHeight = 56;
    const int bottomMargin = 24;
    const int y = (std::max)(0, static_cast<int>(screenHeight_) - buttonHeight - bottomMargin);

    if (startButton_)
    {
        startButton_->SetPosition((static_cast<int>(screenWidth_) - buttonWidth) / 2, y);
        startButton_->SetSize(buttonWidth, buttonHeight);
    }
    if (leftStopButton_)
    {
        leftStopButton_->SetPosition(24, y);
        leftStopButton_->SetSize(buttonWidth, buttonHeight);
    }
    if (rightStopButton_)
    {
        rightStopButton_->SetPosition(
            (std::max)(0, static_cast<int>(screenWidth_) - buttonWidth - 24), y);
        rightStopButton_->SetSize(buttonWidth, buttonHeight);
    }
}

void PlaySceneButton::Reset()
{
    if (timer_)
        timer_->Reset();

    hasResult_ = false;
    resultSide_ = 0;
    resultText_.clear();

    if (startButton_) startButton_->SetActive(true);
    if (leftStopButton_) leftStopButton_->SetActive(false);
    if (rightStopButton_) rightStopButton_->SetActive(false);
}

void PlaySceneButton::OnStartClicked()
{
    if (!timer_ || timer_->IsWaiting() || timer_->IsRunning())
        return;

    static std::mt19937 engine((std::random_device())());
    std::uniform_int_distribution<int> distribution(10, 20);
    timer_->Start(distribution(engine));

    hasResult_ = false;
    resultText_.clear();

    startButton_->SetActive(false);
    leftStopButton_->SetActive(true);
    rightStopButton_->SetActive(true);
}

void PlaySceneButton::OnStopClicked(int side)
{
    if (!timer_ || !timer_->IsRunning())
        return;

    const double elapsed = timer_->Stop();
    resultSide_ = side;
    hasResult_ = true;

    char buffer[64]{};
    std::snprintf(buffer, sizeof(buffer), "%.2f", elapsed);
    resultText_ = buffer;

    leftStopButton_->SetActive(false);
    rightStopButton_->SetActive(false);
    startButton_->SetActive(true);
}

void PlaySceneButton::Draw()
{
    if (!font_ || !timer_ || !ImGui::GetCurrentContext())
        return;

    timer_->Update();

    if (startButton_) startButton_->Draw();
    if (leftStopButton_) leftStopButton_->Draw();
    if (rightStopButton_) rightStopButton_->Draw();

    char buffer[64]{};
    if (timer_->GetTargetSeconds() > 0)
    {
        std::snprintf(buffer, sizeof(buffer), "Target: %d", timer_->GetTargetSeconds());
        font_->Draw(screenWidth_ - 190.0f, 20.0f, buffer, 0xFFFFFFFF);
    }

    if (timer_->IsWaiting())
    {
        font_->Draw(screenWidth_ * 0.5f - 45.0f, 20.0f, "00.00", 0xFFFFFFFF);
    }
    else if (timer_->GetTargetSeconds() > 0)
    {
        std::snprintf(buffer, sizeof(buffer), "%05.2f", timer_->GetElapsedSeconds());
        font_->Draw(screenWidth_ * 0.5f - 45.0f, 20.0f, buffer, 0xFFFFFFFF);
    }

    if (hasResult_)
    {
        const float x = resultSide_ < 0
            ? 24.0f + 48.0f
            : screenWidth_ - 180.0f - 24.0f + 48.0f;
        const float y = screenHeight_ - 56.0f - 24.0f - 36.0f;
        font_->Draw(x, y, resultText_.c_str(), 0xFFFFFFFF);
    }
}
