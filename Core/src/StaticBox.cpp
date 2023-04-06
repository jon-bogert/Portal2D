#include "Pch.h"
#include "StaticBox.h"
#include "Game.h"
#include "Window.h"

StaticBox::StaticBox()
{
	Awake();
}

StaticBox::StaticBox(xe::Vector2 position)
{
	transform.position = position;
	Awake();
}

void StaticBox::Awake()
{
	SetupSprite("test", tempVisual);

	_rigidbody.Setup(Rigidbody::Type::Static, &transform);
	_collider.Setup(_dimensions, this, _rigidbody);

	Game::AddGameObject(this);
}

void StaticBox::Start()
{
}

void StaticBox::Update(const float& deltaTime)
{
}

void StaticBox::PostUpdate(const float& deltaTime)
{
}

void StaticBox::Draw()
{
	Window::Draw(tempVisual, transform);
}

void StaticBox::OnDestroy()
{
}

void StaticBox::OnCollisionEnter(GameObject* other)
{
	std::cout << "StaticBox Collided with othe object" << std::endl;
}
