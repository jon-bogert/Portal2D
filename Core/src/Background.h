#pragma once
#include "GameObject.h"
class Background : public GameObject
{
	xe::Vector2 _initPosition;

	sf::Sprite _sprite;

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void AddOffset(xe::Vector2 offset);
};

