#include "Pch.h"
#include "Level.h"

#include "Tile.h"
#include "Game.h"
#include "Window.h"
#include "XephTools/InputSystem.h"

Level::Level()
{
	Awake();
}

Level::~Level()
{
	Game::RemoveGameObject(this);
}

void Level::Awake()
{
	Game::AddGameObject(this);

	std::vector<int> ids = {
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1
	};
	_dimensions = { 6, 5 };
	for (size_t i = 0; i < ids.size(); ++i)
	{
		_tiles.emplace_back(std::make_unique<Tile>(ids[i]));
		if (_tiles.back()->GetID() > 0)
			_tiles.back()->SetTilePosition(IndexToPos(i).x, IndexToPos(i).y);
	}
}

void Level::Start()
{
}

void Level::Update(const float& deltaTime)
{
	for (auto& tile : _tiles)
	{
		tile->DebugTileDisplay(false);
	}
	xe::Vector2 point = xe::Vector2(3, 2.5);
	xe::Vector2 norm = xe::Normalize(Window::PixelToUnit(xe::InputSystem::MousePosition()) - point);
	Tile* tile = RaycastTile(point, norm);
	if (tile)
		tile->DebugTileDisplay(true);
}

Tile* Level::RaycastTile(xe::Vector2 start, xe::Vector2 castNormal)
{
	if (castNormal == xe::Vector2::Zero())
	{
		std::cout << "RaycastTile(): castNormal cannot be Zero" << std::endl;
		return nullptr;
	}

	xe::Normalize(castNormal);
	bool isVert = (castNormal.x == 0.f);

	float slope = castNormal.y / castNormal.x; // rise over run
	float yOff = start.y - slope * start.x;

	//Get check end-point from castNormal and map size
	xe::Vector2 target =  start + castNormal * CastRange();

	Window::DrawLine(start, target, 5, sf::Color::Green);

	bool isTall = fabs(slope) >= 1.f;
	bool isUp = castNormal.y >= 0.f;
	bool isRight = castNormal.x >= 0.f;

	//tile positions to test;
	int testX{};
	int testY{};
	if (isTall) // check by y
	{
		if (isUp) // check bottom of tile
		{
			testY = (int)start.y + 1; // start at tile above
			while (testY < target.y)
			{
				testX = (isVert) ? (int)start.x : (int)((testY - yOff) / slope);
				Tile* tile = GetTile(testX, testY);
				if (tile->GetID() > 0)
				{
					return tile;
				}
				++testY;
			}
		}
		else // check top of tile
		{
			testY = (int)start.y; // start at tile below
			while (testY > target.y)
			{
				testX = (isVert) ? (int)start.x : (int)((testY - yOff) / slope);
				Tile* tile = GetTile(testX, testY);
				if (tile->GetID() > 0)
				{
					return tile;
				}
				--testY;
			}
		}
	}
	else // check by x
	{
		if (isRight) // check bottom of tile
		{
			testX = (int)start.x + 1; // start at tile right
			while (testX < target.x)
			{
				testY = (int)(slope * testX + yOff);
				Tile* tile = GetTile(testX, testY);
				if (tile->GetID() > 0)
				{
					return tile;
				}
				++testX;
			}
		}
		else // check top of tile
		{
			testX = (int)start.x; // start at tile left
			while (testX > target.x)
			{
				testY = (int)(slope * testX + yOff);
				Tile* tile = GetTile(testX, testY);
				if (tile->GetID() > 0)
				{
					return tile;
				}
				--testX;
			}
		}
	}

	std::cout << "No Raycast Collision found" << std::endl;
	return nullptr;
}

float Level::CastRange() const
{
	return xe::Magnitude(_dimensions);
}

Tile* Level::GetTile(int x, int y)
{
	return _tiles[PosToIndex(x, y)].get();
}

Tile* Level::GetTile(xe::Vector2 pos)
{
	return GetTile((int)pos.x, (int)pos.y);
}

Tile* Level::GetInteractable(int x, int y)
{
	return _interactables[PosToIndex(x, y)].get();
}

Tile* Level::GetInteractable(xe::Vector2 pos)
{
	return GetInteractable((int)pos.x, (int)pos.y);
}

int Level::PosToIndex(int x, int y)
{
	return y * _dimensions.x + x;
}

xe::Vector2 Level::IndexToPos(int index)
{
	return xe::Vector2(index % (int)_dimensions.x, index / (int)_dimensions.x);
}
