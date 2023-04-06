#pragma once

namespace ai
{
	class GridBasedGraph;
}

class Window
{
	sf::RenderWindow* _window = nullptr;

	xe::Vector2 _camera{};

	std::string _title = "Game Title";
	xe::Vector2 _resolution = { 1920, 1080 };
	xe::Vector2 _refResolution = { 1280, 720 };
	float _scale = 1.f; // Set by resolutions;

	int _pixelsPerUnit = 64;

	bool _fullscreenMode = false; // false for debug

	static Window& Get();
	Window();

public:
	~Window();
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;

	static sf::RenderWindow* UnWrap();

	static bool GetIsOpen();
	static void Draw(sf::Sprite& sprite, Transform transfrom);
	static void Draw(sf::Text& text, Transform transfrom);
	static void Draw(sf::RectangleShape& rect, Transform transfrom);

	static void DrawHUD(sf::Sprite& sprite, Transform transfrom);
	static void DrawHUD(sf::Text& text, Transform transfrom);
	static void DrawHUD(sf::RectangleShape& rect, Transform transfrom);

	static void Clear();
	static void Display();
	static void Close();

	static xe::Vector2 GetResolution();
	static void ChangeResolution(const xe::Vector2& resolution);

	static void SetCameraPosition(xe::Vector2 position);
	static void AddCameraPosition(xe::Vector2 position);
	static xe::Vector2 GetCameraPosition();

	static int GetPixelsPerUnit();
	static float GetScale();

	static float WidthInUnits();
	static float HeightInUnits();

	static xe::Vector2 UnitToPixel(xe::Vector2 unitCoord);
	static xe::Vector2 PixelToUnit(xe::Vector2 pixelCoord);

	static void SetCursorVis(const bool visible);
};

