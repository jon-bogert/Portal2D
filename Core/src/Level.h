#pragma once
#include "GameObject.h"

/*
Contents:

dimensions

Tiles Visuals
Player Collision
Interactable Triggers
Some way to get raycast data of whether tile is Portalable

Recalculate Collision Algorithm
*/

class Tile;
class Level : public GameObject
{
	xe::Vector2 _dimensions;
	std::vector<std::unique_ptr<Tile>> _tiles;
	std::vector<std::unique_ptr<Tile>> _interactables;

public:
	Level();
	~Level();

	void Awake();
	void Start() override;
	void Update(const float& deltaTime) override;

	Tile* RaycastTile(xe::Vector2 start, xe::Vector2 castNormal);
	float CastRange() const;

	Tile* GetTile(int x, int y);
	Tile* GetTile(xe::Vector2 pos);
	Tile* GetInteractable(int x, int y);
	Tile* GetInteractable(xe::Vector2 pos);

private:
	int PosToIndex(int x, int y);
	xe::Vector2 IndexToPos(int index);

};