#include "Pch.h"
#include "Tile.h"

#include "Game.h"
#include "Window.h"

Tile::Tile()
{
	Awake();
}

Tile::Tile(int id)
	: _id(id)
{
	Awake();
}

Tile::~Tile()
{
	Game::RemoveGameObject(this);
}

void Tile::Awake()
{
	Game::AddGameObject(this);

	if (_id > 0)
		_doDraw = true;
}

void Tile::Start()
{
	SetupSprite("wall", _sprite);
	_debugOutline.setSize({32, 32});
	_debugOutline.setOrigin({ _sprite.getGlobalBounds().width * 0.5f, _sprite.getGlobalBounds().height * 0.5f });
	_debugOutline.setOutlineColor(sf::Color::Red);
	_debugOutline.setFillColor(sf::Color::Transparent);
}

void Tile::Draw()
{
	if (_doDraw)
	{
		Window::Draw(_sprite, transform);
		_debugOutline.setPosition(_sprite.getPosition());
		Window::UnWrap()->draw(_debugOutline);
	}
}

void Tile::SetTilePosition(int x, int y)
{
	transform.position = xe::Vector2(x + 0.5f, y + 0.5f);
}

xe::Vector2 Tile::GetTilePos() const
{
	return xe::Vector2((int)transform.position.x, (int)transform.position.y);
}

int Tile::GetID() const
{
	return _id;
}

void Tile::DebugTileDisplay(bool isOn)
{
	if (isOn)
	{
		_debugOutline.setOutlineThickness(3);
	}
	else
	{
		_debugOutline.setOutlineThickness(0);
	}
}
