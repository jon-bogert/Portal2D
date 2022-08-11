#include "Pch.h"
#include "Game.h"
#include "Window.h"

void Game::Start()
{
}

void Game::Update(const float& deltaTime)
{
	sf::Event winEvent;
	while (Window::Get().UnWrap()->pollEvent(winEvent))
	{
		// "close requested" event: we close the window
		if (winEvent.type == sf::Event::Closed)
			Window::Get().UnWrap()->close();
	}
}

void Game::Draw()
{
	Window::Get().UnWrap()->clear({ 0, 0, 0, 255 });

	Window::Get().UnWrap()->display();
}

void Game::OnDestroy()
{
}
