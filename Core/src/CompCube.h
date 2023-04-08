#pragma once
#include "GameObject.h"
#include "Physics.h"

class CompCube : public GameObject
{
	Rigidbody _rigidbody;
	BoxCollider _collider;

	sf::Sprite tempVisual;

	bool _doTeleport = false;
	xe::Vector2 _teleportPosition;

public:
	CompCube();
	CompCube(xe::Vector2 position);

	void Awake();
	void Start() override;
	void Update(const float& deltaTime) override;
	void PostUpdate(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void OnCollisionEnter(GameObject* other) override;
	void OnTriggerEnter(GameObject* other) override;
	void OnTriggerExit(GameObject* other) override;

	void Teleport(xe::Vector2 pos, xe::Vector2 newVelocity);

	xe::Vector2 GetVelocity() const;
};