#include "Pch.h"
#include "Portal.h"
#include "Game.h"
#include "Window.h"

Portal::Portal()
{
	Awake();
}

Portal::Portal(xe::Vector2 position, Direction direction, Color color, Portal* other)
	: _direction(direction)
	, _color(color)
	, _pair(other)
{
	transform.position = position;
	Awake();
}

void Portal::Awake()
{
	if (_color == Color::Blue)
		SetupSprite("testportal-blue", _sprite);
	else
		SetupSprite("testportal-orange", _sprite);
	_dimensions = { 0.25f, 1.f };

	switch (_direction)
	{
	case Direction::Up:
		transform.rotation.SetDeg(90.f);
		break;
	case Direction::Right:
		transform.rotation.SetDeg(180.f);
		break;
	case Direction::Down:
		transform.rotation.SetDeg(270.f);
		break;
	}

	_rigidbody.Setup(Rigidbody::Type::Static, &transform);
	_collider.Setup(_dimensions, this, _rigidbody, PhysicsMaterial(), true);

	Game::AddGameObject(this);
}

void Portal::Draw()
{
	Window::Draw(_sprite, transform);
}

void Portal::OnTriggerEnter(GameObject* other)
{
	if (other->GetTag() == "CompCube" && other != _waitForExit)
	{
		((CompCube*)other)->NewPosition(_pair->transform.position);
		_pair->AddWaitForExit(other);
		std::cout << "CompCube Detected" << std::endl;
	}
}

void Portal::OnTriggerExit(GameObject* other)
{
	if (other == _waitForExit)
		_waitForExit = nullptr;
}

Direction Portal::GetDirection() const
{
	return _direction;
}

Portal::Color Portal::GetColor() const
{
	return _color;
}

void Portal::AddWaitForExit(GameObject* obj)
{
	_waitForExit = obj;
}
