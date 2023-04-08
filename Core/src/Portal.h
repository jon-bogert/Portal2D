#pragma once
#include "GameObject.h"
#include "TileMap.h"
#include "Physics.h"

class Portal : public GameObject
{
public:
	enum Color {Blue, Orange};

private:
	Direction _direction = Direction::Left;
	Color _color = Color::Blue;

	Portal* _partner = nullptr;

	sf::Sprite _sprite;

	Rigidbody _rigidbody;
	BoxCollider _collider;

	GameObject* _waitForExit = nullptr;

public:
	Portal();
	Portal(xe::Vector2 position, Direction direction, Color color);
	~Portal();

	void Awake();
	void Draw();

	void OnTriggerEnter(GameObject* other) override;
	void OnTriggerExit(GameObject* other) override;

	//Getters & Setters
	Direction GetDirection() const;
	Color GetColor() const;

	void SetPartner(Portal* partner);
	void ChangePosition(xe::Vector2 newPosition, Direction direction);

	void AddWaitForExit(GameObject* obj);
	xe::Vector2 GetNormal();

private:
	static xe::Vector2 RotateVector(xe::Vector2 vec, xe::Vector2 norm1, xe::Vector2 norm2);
	static float GetRotation(Direction dir);


};