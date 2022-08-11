#pragma once
#include "Entity.h"

class TestChamber : public Entity
{
	sf::Vector2i dimensions; // in tiles
	std::vector<int> tileMapOriginal;
	std::vector<int> tileMapCurrent;
	std::string filePath;
public:
	TestChamber(std::string path);
	virtual ~TestChamber();

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void Reset();

private:
	void LoadFromFile();
};

