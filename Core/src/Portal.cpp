#include "Pch.h"
#include "Portal.h"
#include "Game.h"
#include "Window.h"

Portal::Portal()
{
	Awake();
}

Portal::Portal(xe::Vector2 position, Direction direction, Color color)
	: _direction(direction)
	, _color(color)
{
	transform.position = position;
	Awake();
}

Portal::~Portal()
{
	Game::RemoveGameObject(this);
}

void Portal::Awake()
{
	if (_color == Color::Blue)
		SetupSprite("testportal-blue", _sprite);
	else
		SetupSprite("testportal-orange", _sprite);
	_dimensions = { 0.25f, 1.f };

	transform.rotation.SetDeg(GetRotation(_direction));

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
		CompCube* cube = (CompCube*)other;
		xe::Vector2 newVelocity = RotateVector(cube->GetVelocity(), GetNormal(), _partner->GetNormal());

		cube->Teleport(_partner->transform.position, newVelocity);
		_partner->AddWaitForExit(other);
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

void Portal::SetPartner(Portal* partner)
{
	_partner = partner;
}

void Portal::ChangePosition(xe::Vector2 newPosition, Direction direction)
{
	transform.position = newPosition;
	transform.rotation.SetDeg(GetRotation(direction));
	_rigidbody->SetTransform(transform.position, -transform.rotation.GetRad());
}

void Portal::AddWaitForExit(GameObject* obj)
{
	_waitForExit = obj;
}

xe::Vector2 Portal::GetNormal()
{
	switch (_direction)
	{
	case Direction::Left:
		return { -1.f, 0.f };
	case Direction::Up:
		return { 0.f, 1.f };
	case Direction::Right:
		return { 1.f, 0.f };
	case Direction::Down:
		return { 0.f, -1.f };
	default:
		return xe::Vector2::Zero();
	}
}

xe::Vector2 Portal::RotateVector(xe::Vector2 vec, xe::Vector2 norm1, xe::Vector2 norm2)
{
	norm1 *= -1.f;
	float angle = std::acosf(xe::Dot(norm1, norm2));
	angle *= std::signbit(norm1.x * norm2.y - norm1.y * norm2.x) ? -1 : 1;

	float c = std::cos(angle);
	float s = std::sin(angle);

	return xe::Vector2(c * vec.x - s * vec.y, s * vec.x + c * vec.y);
}

float Portal::GetRotation(Direction dir)
{
	switch (dir)
	{
	case Direction::Up:
		return 90.f;
	case Direction::Right:
		return 180.f;
	case Direction::Down:
		return 270.f;
	default:
		return 0.f;
	}
}
