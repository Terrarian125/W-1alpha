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

	void Run();
	void Jump();
	void NockBack();

	void OnCollision(GameObject* pTarget) override;
private:
	int hModel_;
	float speed_;

	XMFLOAT3 colPos_;

	float velocity_;
	float gravity_;
	float jumpPower_;

	XMFLOAT3 knockbackVelocity_;
	float knockbackTime_;

	bool isGround_;
};