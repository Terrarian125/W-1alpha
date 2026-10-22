#pragma once
#include "../Engine/GameObject.h"

// 障害物クラスを管理するクラス
class Obstacle : public GameObject
{
public:
	Obstacle(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
};