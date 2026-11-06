#include "Player.h"

#include "Engine/InputBinding.h"

#include "Bin.h"
#include "Beermug.h"

Player::Player(GameObject* _pParent) :
    GameObject(_pParent, "Player"),
    inputSet_(),
    pBin_(),
    pBeermug_()
{
}

void Player::Initialize()
{
    playerID_ = playerCount_;
    objectName_ = "Player" + std::to_string(playerID_);

    pBin_ = Instantiate<Bin>(this);
    pBin_->SetObjectName("Bin" + std::to_string(playerID_));
    pBin_->SetRotateZ(-20.f);
    pBin_->SetScale(0.1f);

    // Transform parent is Table
    pBeermug_ = Instantiate<Beermug>(GetParent());
    pBeermug_->SetObjectName("Beermug" + std::to_string(playerID_));
    pBeermug_->SetPosition(-0.25, 0, 0);
    if (playerID_ == 1)
    {
        pBeermug_->SetPosition(0.25, 0, 0);
        pBeermug_->SetModelIndex(Beermug::BeermugVariation::BEERMUG_CROSS_SECTION_R);
    }
    pBeermug_->SetScale(0.15f);

    playerCount_ += 1;
}

void Player::Update()
{
    if (IsHold(inputSet_.at(PlayerAction::POUR)))
    {
        pBin_->Pouring();
    }

    if (IsDown(inputSet_.at(PlayerAction::CONFIRMED)))
    {
        pBin_->Conform();
    }
}

void Player::Draw()
{
}

void Player::Release()
{
}
