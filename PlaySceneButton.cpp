#include "PlaySceneButton.h"
#include "Engine/Input.h"
#include <imgui.h>
#include <algorithm>
#include <cstdio>
#include <random>
#include <cmath>
#include <string>

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

    leftPressed_ = false;
    rightPressed_ = false;
    hasResult_ = false;
    gameFinished_ = false;
    leftTime_ = 0.0;
    rightTime_ = 0.0;
    leftFalseStarts_ = 0;
    rightFalseStarts_ = 0;
    winnerSide_ = 0;
    resultText_.clear();

    if (startButton_) startButton_->SetActive(true);
    if (leftStopButton_) leftStopButton_->SetActive(false);
    if (rightStopButton_) rightStopButton_->SetActive(false);
}

void PlaySceneButton::OnStartClicked()
{
    if (!timer_ || timer_->IsWaiting() || timer_->IsRunning())
        return;

    //新しいゲーム開始時はフライング回数をリセット
    leftFalseStarts_ = 0;
    rightFalseStarts_ = 0;
    leftPressed_ = false;
    rightPressed_ = false;
    hasResult_ = false;
    gameFinished_ = false;
    leftTime_ = 0.0;
    rightTime_ = 0.0;
    winnerSide_ = 0;
    resultText_.clear();

    static std::mt19937 engine((std::random_device())());
    std::uniform_int_distribution<int> distribution(10, 20);
    timer_->Start(distribution(engine));

    startButton_->SetActive(false);
    leftStopButton_->SetActive(true);
    rightStopButton_->SetActive(true);
}

void PlaySceneButton::ResetRound(bool restartTimer)
{
    leftPressed_ = false;
    rightPressed_ = false;
    leftTime_ = 0.0;
    rightTime_ = 0.0;
    hasResult_ = false;
    gameFinished_ = false;
    winnerSide_ = 0;
    resultText_.clear();

    if (leftStopButton_) leftStopButton_->SetActive(true);
    if (rightStopButton_) rightStopButton_->SetActive(true);
    if (startButton_) startButton_->SetActive(false);

    if (restartTimer && timer_)
        timer_->Start(timer_->GetTargetSeconds());
}

void PlaySceneButton::OnStopClicked(int side)
{
    if (!timer_ || !timer_->IsRunning() || gameFinished_)
        return;

    const double elapsed = timer_->GetElapsedSeconds();
    const double target = static_cast<double>(timer_->GetTargetSeconds());

    //ターゲット時間より前ならフライング。Xを加算して両者とも再挑戦。
    if (elapsed < target)
    {
        if (side < 0)
            ++leftFalseStarts_;
        else
            ++rightFalseStarts_;

        ResetRound(true);
        return;
    }

    //このプレイヤーの押下時刻を記録。タイマー自体は止めない。
    if (side < 0)
    {
        if (leftPressed_)
            return;

        leftPressed_ = true;
        leftTime_ = elapsed;
        leftStopButton_->SetActive(false);
    }
    else
    {
        if (rightPressed_)
            return;

        rightPressed_ = true;
        rightTime_ = elapsed;
        rightStopButton_->SetActive(false);
    }

    //L/R両方の押下が揃った時点で勝敗判定
    if (leftPressed_ && rightPressed_)
    {
        hasResult_ = true;
        gameFinished_ = true;

        const double leftDifference = std::abs(leftTime_ - target);
        const double rightDifference = std::abs(rightTime_ - target);

        if (leftDifference < rightDifference)
        {
            winnerSide_ = -1;
            resultText_ = "L WIN";
        }
        else if (rightDifference < leftDifference)
        {
            winnerSide_ = 1;
            resultText_ = "R WIN";
        }
        else
        {
            winnerSide_ = 0;
            resultText_ = "DRAW";
        }

        //2人とも押したのでタイマーを止める（押下時刻は個別に記録済み）。
        timer_->Stop();

        //リザルト画面へ
        //SceneManager::ChangeScene();
        startButton_->SetActive(true);
    }
}

void PlaySceneButton::Draw()
{
    //コントローラー0：AボタンでL側のSTOP
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 0))
    {
        OnStopClicked(-1);
    }

    //コントローラー1：AボタンでR側のSTOP
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 1))
    {
        OnStopClicked(1);
    }

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

    //各ボタンの下にフライング回数をXで表示
    const float resultY = screenHeight_ - 56.0f - 24.0f - 36.0f;
    std::string leftMarks;
    std::string rightMarks;
    for (int i = 0; i < leftFalseStarts_; ++i) leftMarks += "X ";
    for (int i = 0; i < rightFalseStarts_; ++i) rightMarks += "X ";

    if (!leftMarks.empty())
        font_->Draw(24.0f + 48.0f, resultY + 28.0f, leftMarks.c_str(), 0xFFFF5555);
    if (!rightMarks.empty())
        font_->Draw(screenWidth_ - 180.0f - 24.0f + 48.0f,
            resultY + 28.0f, rightMarks.c_str(), 0xFFFF5555);

    //押した瞬間の時間を、それぞれのボタンの近くに表示
    if (leftPressed_)
    {
        std::snprintf(buffer, sizeof(buffer), "%.2f", leftTime_);
        font_->Draw(24.0f + 48.0f, resultY, buffer, 0xFFFFFFFF);
    }
    if (rightPressed_)
    {
        std::snprintf(buffer, sizeof(buffer), "%.2f", rightTime_);
        font_->Draw(screenWidth_ - 180.0f - 24.0f + 48.0f,
            resultY, buffer, 0xFFFFFFFF);
    }

    if (hasResult_)
        font_->Draw(screenWidth_ * 0.5f - 40.0f, resultY - 40.0f,
            resultText_.c_str(), 0xFFFFFFFF);
}