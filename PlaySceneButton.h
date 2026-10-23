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

    float screenWidth_ = 800.0f;
    float screenHeight_ = 600.0f;
    FontText* font_ = nullptr;
    GameTimer* timer_ = nullptr;

    std::unique_ptr<GuiButton> startButton_;
    std::unique_ptr<GuiButton> leftStopButton_;
    std::unique_ptr<GuiButton> rightStopButton_;

    bool hasResult_ = false;
    int resultSide_ = 0;
    std::string resultText_;
};
