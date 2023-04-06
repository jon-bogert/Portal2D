#include "Pch.h"
#include "InstructionsScreen.h"
#include "Button.h"
#include "Window.h"
#include "GameObject.h"
#include "Background.h"
#include "AssetManager.h"

namespace Application
{
	extern GameState nextState; // Defined in Main.cpp
}

InstructionsScreen& InstructionsScreen::Get()
{
	static InstructionsScreen instance;
	return instance;
}

InstructionsScreen::InstructionsScreen()
{
}

InstructionsScreen::~InstructionsScreen()
{
}

void InstructionsScreen::Start()
{
	Get()._bg = new Background();
	Get()._instr.setTexture(*AssetManager::GetTexture("instructions"));
	Get()._instr.setScale(Window::GetResolution().x / Get()._instr.getLocalBounds().width, Window::GetResolution().y / Get()._instr.getLocalBounds().height);

	Get()._quitButton = new Button("Back to Main Menu", 7, 1);
	Get()._quitButton->transform.position =  xe::Vector2(Window::WidthInUnits() * 0.5f, 3);

	Get()._quitButton->SetEvent(BUTTON_CALLBACK_GET(InstructionsScreen::MainMenu));

	Get()._bg->Start();
	Get()._quitButton->Start();
}

void InstructionsScreen::Update(const float& deltaTime)
{
	Get()._quitButton->Update(deltaTime);
}

void InstructionsScreen::Draw()
{
	Get()._bg->Draw();
	Get()._quitButton->Draw();
	Window::UnWrap()->draw(Get()._instr);
}

void InstructionsScreen::OnDestroy()
{
	Get()._bg->OnDestroy();
	Get()._quitButton->OnDestroy();

	delete Get()._bg;
	delete Get()._quitButton;

	Get()._bg = nullptr;
	Get()._quitButton = nullptr;
}

void InstructionsScreen::MainMenu()
{
	Application::nextState = GameState::MainMenu;
}
