#pragma once

class Button;
class Background;
class MainMenu
{
	std::string _titleStr = "Game Title";

	Button* _startButton = nullptr;
	Button* _quitButton = nullptr;
	Button* _instrButton = nullptr;

	Background* _bg = nullptr;

	sf::Text _title;
	Transform _titleTransform;

	static MainMenu& Get();
	MainMenu();

public:
	virtual ~MainMenu();
	MainMenu(const MainMenu& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;

	static void Start();
	static void Update(const float& deltaTime);
	static void Draw();
	static void OnDestroy();

private:
	void StartGame();
	void Instructions();
	void QuitToDesktop();
};