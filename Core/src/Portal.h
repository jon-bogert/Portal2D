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

	Portal* _pair = nullptr;

	sf::Sprite _sprite;

	Rigidbody _rigidbody;
	BoxCollider _collider;

	GameObject* _waitForExit = nullptr;

public:
	Portal();
	Portal(xe::Vector2 position, Direction direction, Color color, Portal* other = nullptr);

	void Awake();
	void Draw();

	void OnTriggerEnter(GameObject* other) override;
	void OnTriggerExit(GameObject* other) override;

	//Getters & Setters
	Direction GetDirection() const;
	Color GetColor() const;

	void AddWaitForExit(GameObject* obj);


};