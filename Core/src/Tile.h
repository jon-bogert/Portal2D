#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
	int _id = 0;
	sf::Sprite _sprite;
	bool _doDraw = false;

public:
	Tile();
	Tile(int id);
	~Tile();

	void Awake();
	void Start() override;
	void Draw() override;

	void SetTilePosition(int x, int y);
	xe::Vector2 GetTilePos() const;
	int GetID() const;

};