#pragma once
#include "GameObject.h"
#define BUTTON_CALLBACK(function, objPtr) std::bind(&function, this)
#define BUTTON_CALLBACK_GET(function, objPtr) std::bind(&function, &Get())

class Button : public GameObject
{
	sf::RectangleShape _plate;
	sf::Text _text;
	sf::Sound _hoverSound;
	sf::Sound _selectSound;

	float _fontSize = 20.f;
	sf::Color _activeColor = {180, 180, 180, 127};
	sf::Color _inactiveColor = { 127, 127, 127, 127 };

	float _width;
	float _height;
	bool _hoverTrigger = false;

	std::function<void()> _clickEvent;

public:
	Button(std::string text, int width, int height);

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void SetEvent(std::function<void()> clickEvent);

private:
	bool CheckHover();
	void ClickEvent();
};

