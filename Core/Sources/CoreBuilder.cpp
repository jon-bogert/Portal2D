#include "Pch.h"

#define DEBUG_MODE true

int WinMain()
{
	Debug::Setup(DEBUG_MODE);

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{

	}

	Debug::ShutDown();
	return 0;
}