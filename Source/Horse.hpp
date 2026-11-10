#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/BoxCollider.h"

class Horse : public GameObject
{
public:
	Horse(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hModel_;
	float speed_;

	float velocity_;
	float gravity_;
	float jumpPower_;

	bool isGround_;
};