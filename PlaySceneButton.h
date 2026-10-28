#pragma once

#include "Engine/GuiButton.h"
#include "Engine/FontText.hpp"
#include "Engine/GameTimer.h"

#include <memory>
#include <string>

class PlaySceneButton
{
public:
    PlaySceneButton() = default;
    ~PlaySceneButton() = default;

    PlaySceneButton(const PlaySceneButton&) = delete;
    PlaySceneButton& operator=(const PlaySceneButton&) = delete;

    bool Initialize(float screenWidth, float screenHeight,
        FontText* font, GameTimer* timer);
    void Draw();
    void SetScreenSize(float screenWidth, float screenHeight);
    void Reset();

private:
    void OnStartClicked();
    void OnStopClicked(int side);
    void UpdateButtonPositions();
    void ResetRound(bool restartTimer);

    float screenWidth_ = 800.0f;
    float screenHeight_ = 600.0f;
    FontText* font_ = nullptr;
    GameTimer* timer_ = nullptr;

    std::unique_ptr<GuiButton> startButton_;
    std::unique_ptr<GuiButton> leftStopButton_;
    std::unique_ptr<GuiButton> rightStopButton_;

    bool leftPressed_ = false;
    bool rightPressed_ = false;
    bool hasResult_ = false;
    bool gameFinished_ = false;

    double leftTime_ = 0.0;
    double rightTime_ = 0.0;
    int leftFalseStarts_ = 0;
    int rightFalseStarts_ = 0;
    int winnerSide_ = 0; // -1: 左、1: 右、0: 引き分け
    std::string resultText_;
};
