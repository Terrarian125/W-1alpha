#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/Collider.h"

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
	int hModel_; // モデルのハンドル
};