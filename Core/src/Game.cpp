#include "Pch.h"
#include "Game.h"

#include "AssetManager.h"
#include "Window.h"
#include "GameObject.h"
#include "TileData.h"

namespace Application
{
	extern GameState nextState; // Defined in CoreBuilder.cpp
}

Game& Game::Get()
{
	static Game instance;
	return instance;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
	//Escape to Go to Main Menu -v
	xe::InputSystem::Subscribe(xe::Key::Escape, xe::Pressed,
		std::bind(&Game::QuitToMain, &Get()), static_cast<void*>(&Get()));
	Get().fps.setCharacterSize(12);
	Get().fps.setFont(*AssetManager::GetFont("default"));
	Get().fps.setFillColor(sf::Color::White);

	Get()._testCube = std::make_unique<CompCube>(xe::Vector2(5, 5));
	Get()._testPortal2 = std::make_unique<Portal>(xe::Vector2(10, 5), Direction::Up, Portal::Color::Orange);
	Get()._testPortal1 = std::make_unique<Portal>(xe::Vector2(5, 0), Direction::Up, Portal::Color::Blue, Get()._testPortal2.get());

	for (GameObject* obj : Get()._gameObjects)
		obj->Start();
}

void Game::Update(const float& deltaTime)
{
	for (GameObject* obj : Get()._gameObjects)
		obj->Update(deltaTime);

	if (Get().showFPS)
	{
		std::string fpsStr = (deltaTime == 0) ? std::to_string(0) : std::to_string(static_cast<int>((1 / deltaTime) + 0.5f));
		Get().fps.setString(fpsStr);
	}
}

void Game::LateUpdate(const float& deltaTime)
{
	for (GameObject* obj : Get()._gameObjects)
		obj->LateUpdate(deltaTime);
}

void Game::PostUpdate(const float& deltaTime)
{
	for (GameObject* obj : Get()._gameObjects)
		obj->PostUpdate(deltaTime);
}

void Game::Draw()
{
	for (GameObject* obj : Get()._drawBuffer)
		obj->Draw();

	if (Get().showFPS)
	{
		Get().fps.setPosition({ Window::GetResolution().x - Get().fps.getLocalBounds().width, 0.f });
		Window::UnWrap()->draw(Get().fps);
	}
}

void Game::OnDestroy()
{
	for (GameObject* obj : Get()._gameObjects)
		obj->OnDestroy();

	xe::InputSystem::Unsubscribe(xe::Key::Escape, xe::Pressed, static_cast<void*>(&Get()));
	Window::SetCameraPosition({ 0.f, 0.f });
}

void Game::AddGameObject(GameObject* obj)
{
	if (std::find(Get()._gameObjects.begin(), Get()._gameObjects.end(), obj) != Get()._gameObjects.end())
	{
		std::cout << "GameObject was already found" << std::endl;
		return;
	}
	Get()._gameObjects.push_back(obj);
	Get()._drawBuffer.push_back(obj);
	std::sort(Get()._drawBuffer.begin(),
		Get()._drawBuffer.end(),
		[](const GameObject* a, const GameObject* b) -> bool
		{ return a->GetDrawLayer() < b->GetDrawLayer(); });
}

void Game::RemoveGameObject(GameObject* obj)
{
	auto iter = std::find(Get()._gameObjects.begin(), Get()._gameObjects.end(), obj);
	if (iter == Get()._gameObjects.end())
	{
		std::cout << "GameObject could was not found and could not be removed" << std::endl;
		return;
	}
	Get()._gameObjects.erase(iter);
	Get()._drawBuffer.erase(iter);
}

void Game::ClearGameObjects()
{
	Get()._gameObjects.clear();
	Get()._drawBuffer.clear();
}

void Game::QuitToMain()
{
	Application::nextState = GameState::MainMenu;
}
