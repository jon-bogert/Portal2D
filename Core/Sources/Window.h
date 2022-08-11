#pragma once
class Window
{
	sf::RenderWindow* window = nullptr;

	sf::Vector2f resolution = { 1280, 720 };
	sf::Vector2f refResolution = { 1920, 1080 };
	float scaleFactor;

	Window();

public:
	static Window& Get();
	sf::RenderWindow* UnWrap();

	~Window();
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
};

