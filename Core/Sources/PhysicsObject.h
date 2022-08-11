#pragma once
#include "GameObject.h"

enum class PhysicsType
{
	Static,
	Dynamic,
	Kinematic
};

class PhysicsObject : public GameObject
{
protected:
	PhysicsType type = PhysicsType::Static;
	sf::FloatRect boxCollider = { 0.f, 0.f, 0.f, 0.f };

	float mass = 30.f;

public:
	PhysicsObject() {};
	virtual ~PhysicsObject() {};

	virtual void Start() override = 0;
	virtual void Update(const float& deltaTime) override = 0;
	virtual void Draw() override = 0;
	virtual void OnDestroy() override = 0;

	sf::FloatRect* GetBoxCollider();
	void UpdateCollider();

	bool GetCollision(PhysicsObject* other);

};

