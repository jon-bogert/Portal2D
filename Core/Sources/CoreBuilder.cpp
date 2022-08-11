#include "Pch.h"
#include "Window.h"
#include "Game.h"
#include "TextureManager.h"

#define DEBUG_MODE true

int WinMain()
{
	Debug::Setup(DEBUG_MODE);
	TextureManager::Load();
	Window::Get(); // Instantiate
	Game* game = new Game;

	game->Start();
	while (Window::Get().UnWrap()->isOpen())
	{
		game->Update(1 / 60.f);
		game->Draw();
	}

	game->OnDestroy();

	delete game;
	game = nullptr;

	TextureManager::Unload();
	Debug::ShutDown();
	return 0;
}