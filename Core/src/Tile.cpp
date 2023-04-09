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
	SetupSprite("test", _sprite);
}

void Tile::Draw()
{
	if (_doDraw) Window::Draw(_sprite, transform);
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
