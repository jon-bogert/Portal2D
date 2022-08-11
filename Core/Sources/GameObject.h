#pragma once
#include "Entity.h"
struct Transform
{
	sf::Vector2f position;
	float rotation = 0.f;
	sf::Vector2f scale;

	void FixRotation();
};

class GameObject : public Entity
{
protected:
	Transform transform;

public:
	virtual void Start() override = 0;
	virtual void Update(const float& deltaTime) override = 0;
	virtual void Draw() override = 0;
	virtual void OnDestroy() override = 0;
};

