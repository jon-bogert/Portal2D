#pragma once
#include "CompCube.h"
#include "StaticBox.h"

class GameObject;
class Game
{
	sf::Text fps;
	bool showFPS = true;

	std::vector<GameObject*> _gameObjects;
	std::vector<GameObject*> _drawBuffer;

	std::unique_ptr<CompCube> _testCube;
	std::unique_ptr<StaticBox> _testCube2;

	static Game& Get();
	Game();

public:
	virtual ~Game();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

	static void Start();
	static void Update(const float& deltaTime);
	static void LateUpdate(const float& deltaTime);
	static void PostUpdate(const float& deltaTime);
	static void Draw();
	static void OnDestroy();

	static void AddGameObject(GameObject* obj);
	static void RemoveGameObject(GameObject* obj);
	static void ClearGameObjects();

private:
	void QuitToMain();
};

