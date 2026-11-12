#include "Player.h"

#include <imgui.h>

#include "Engine/InputBinding.h"

#include "Bin.h"
#include "Beermug.h"
#include "Judge.h"

#include "Engine/Text.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"

Player::Player(GameObject* _pParent) :
    GameObject(_pParent, "Player"),
    inputSet_(),
    pBin_(),
    pBeermug_(),
    playerID_(0)
{
}

void Player::Initialize()
{
    pPlayerNameText_ = new Text();
    pPlayerNameText_->Initialize();

    playerID_ = playerCount_ + 1;
    objectName_ = "Player" + std::to_string(playerID_);

    pBin_ = Instantiate<Bin>(this);
    pBin_->SetObjectName("Bin" + std::to_string(playerID_));
    pBin_->SetRotateZ(-20.f);
    pBin_->SetScale(0.1f);

    // Transform parent is Table
    pBeermug_ = Instantiate<Beermug>(GetParent());
    pBeermug_->SetObjectName("Beermug" + std::to_string(playerID_));
    pBeermug_->SetPosition(-0.25, 0, 0);
    if (playerID_ == 2)
    {
        pBeermug_->SetPosition(0.25, 0, 0);
        pBeermug_->SetModelIndex(Beermug::BeermugVariation::BEERMUG_CROSS_SECTION_R);
    }
    pBeermug_->SetScale(0.15f);

    playerCount_ += 1;
}

void Player::Update()
{
    bool stickInputPouring{ Input::GetPadStickL(playerID_ - 1).y >= 0.5f };
    if (IsHold(inputSet_.at(PlayerAction::POUR)) or stickInputPouring)
    {
        pBin_->Pouring();
    }

    bool stickInputConform{ Input::GetPadStickL(playerID_ - 1).y <= -0.5f };
    if ((IsDown(inputSet_.at(PlayerAction::CONFIRMED)) and not(pBin_->IsConfirmed())) or
        stickInputConform and not(pBin_->IsConfirmed()))
    {
        pBin_->Conform();
        Judge::confirmedCount += 1;
    }
}

void Player::Draw()
{
    XMFLOAT2 textPos{};

    textPos = pPlayerNameText_->GetScreenPos(transform_);
    textPos.y += 100.f;
    pPlayerNameText_->Draw((int)textPos.x, (int)textPos.y, objectName_.c_str());
}

void Player::Release()
{
    playerCount_ = 0;
}

float Player::GetWaterLevel()
{
    return pBeermug_->GetWaterLevel();
}
