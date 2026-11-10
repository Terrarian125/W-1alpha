#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/BoxCollider.h"
#include  "../Engine/SphereCollider.h"

// 障害物クラスを管理するクラス
class Obstacle : public GameObject
{
public:
	Obstacle(GameObject* parent, const char* name);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

protected:
	void SetBoxCollider(XMFLOAT3 center, XMFLOAT3 size);

	int hModel_;

	BoxCollider* bCollider_;
	SphereCollider* sCollider_;

	bool isColl_;

	XMFLOAT3 basePos_;
	XMFLOAT3 size_;
};