#include "Pch.h"
#include "Window.h"

Window::Window()
{
    scaleFactor = resolution.y / (float)refResolution.y;
    window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), "Portal2D", sf::Style::Close);

    Debug::Log("Creating Window with dimensions X:%i Y:%i", (int)resolution.x, (int)resolution.y);
    Debug::Log("Scale Factor set to: %f", scaleFactor);
}

Window& Window::Get()
{
    static Window instance;
    return instance;
}

sf::RenderWindow* Window::UnWrap()
{
    return window;
}

Window::~Window()
{
    delete window;
}
