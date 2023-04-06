#pragma once
#include "GameObject.h"
#include "Physics.h"

class StaticBox : public GameObject
{
	Rigidbody _rigidbody;
	BoxCollider _collider;

	sf::Sprite tempVisual;

public:
	StaticBox();
	StaticBox(xe::Vector2 position);

	void Awake();
	void Start() override;
	void Update(const float& deltaTime) override;
	void PostUpdate(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void OnCollisionEnter(GameObject* other) override;
};