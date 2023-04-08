#include "Pch.h"
#include "CompCube.h"
#include "Window.h"
#include "Game.h"

CompCube::CompCube()
{
	Awake();
}

CompCube::CompCube(xe::Vector2 position)
{
	transform.position = position;
	Awake();
}

void CompCube::Awake()
{
	SetupSprite("test", tempVisual);
	_dimensions = { 0.5f, 0.5f };
	_tag = "CompCube";

	_rigidbody.Setup(Rigidbody::Type::Dynamic, &transform);
	_collider.Setup(_dimensions, this, _rigidbody);

	Game::AddGameObject(this);
}

void CompCube::Start()
{
}

void CompCube::Update(const float& deltaTime)
{
}

void CompCube::PostUpdate(const float& deltaTime)
{
	_rigidbody.UpdateTransform();
}

void CompCube::Draw()
{
	Window::Draw(tempVisual, transform);
}

void CompCube::OnDestroy()
{
}

void CompCube::OnCollisionEnter(GameObject* other)
{
	std::cout << "CompCube Collided with other object" << std::endl;
}

void CompCube::OnTriggerEnter(GameObject* other)
{
	std::cout << "CompCube Entered a trigger" << std::endl;
}

void CompCube::OnTriggerExit(GameObject* other)
{
	std::cout << "CompCube Left a trigger" << std::endl;
}

void CompCube::Teleport(xe::Vector2 pos, xe::Vector2 newVelocity)
{
	_rigidbody->SetTransform(pos, _rigidbody->GetAngle());
	_rigidbody->SetLinearVelocity(newVelocity);
}

xe::Vector2 CompCube::GetVelocity() const
{
	return _rigidbody.GetVelocity();
}
