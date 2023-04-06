#pragma once
class Button;
class Background;
class InstructionsScreen
{

	Button* _quitButton = nullptr;

	Background* _bg = nullptr;

	sf::Sprite _instr;

	static InstructionsScreen& Get();
	InstructionsScreen();
public:
	virtual ~InstructionsScreen();
	InstructionsScreen(const InstructionsScreen& other) = delete;
	InstructionsScreen& operator=(const InstructionsScreen& other) = delete;

	static void Start();
	static void Update(const float& deltaTime);
	static void Draw();
	static void OnDestroy();

private:
	void MainMenu();
};
