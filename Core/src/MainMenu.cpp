#include "Pch.h"
#include "MainMenu.h"
#include "Button.h"
#include "Window.h"
#include "GameObject.h"
#include "Background.h"
#include "AssetManager.h"

namespace Application
{
	extern GameState nextState; // Defined in CoreBuilder.cpp
}

MainMenu& MainMenu::Get()
{
	static MainMenu instance;
	return instance;
}

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
	Get()._bg = new Background();

	Get()._title.setFont(*AssetManager::GetFont("default"));
	Get()._title.setString(Get()._titleStr);
	Get()._title.setCharacterSize(72);
	Get()._title.setScale(Window::GetScale(), Window::GetScale());
	Get()._title.setOrigin(Get()._title.getLocalBounds().width * 0.5f, Get()._title.getLocalBounds().height * 0.5f);
	Get()._titleTransform.position = xe::Vector2(Window::WidthInUnits() * 0.5f, 15 );

	Get()._startButton = new Button("Start Game", 5, 1);
	Get()._startButton->transform.position = xe::Vector2(Window::WidthInUnits() * 0.5f, 7);

	Get()._instrButton = new Button("Instructions", 6, 1);
	Get()._instrButton->transform.position = xe::Vector2(Window::WidthInUnits() * 0.5f, 5.5f);

	Get()._quitButton = new Button("Quit to Desktop", 7, 1);
	Get()._quitButton->transform.position = xe::Vector2(Window::WidthInUnits() * 0.5f, 4);

	Get()._startButton->SetEvent(BUTTON_CALLBACK_GET(MainMenu::StartGame));
	Get()._instrButton->SetEvent(BUTTON_CALLBACK_GET(MainMenu::Instructions));
	Get()._quitButton->SetEvent(BUTTON_CALLBACK_GET(MainMenu::QuitToDesktop));

	Get()._bg->Start();
	Get()._startButton->Start();
	Get()._instrButton->Start();
	Get()._quitButton->Start();
}

void MainMenu::Update(const float& deltaTime)
{
	Get()._startButton->Update(deltaTime);
	Get()._instrButton->Update(deltaTime);
	Get()._quitButton->Update(deltaTime);
}

void MainMenu::Draw()
{
	Get()._bg->Draw();
	Window::Draw(Get()._title, Get()._titleTransform);
	Get()._startButton->Draw();
	Get()._instrButton->Draw();
	Get()._quitButton->Draw();
}

void MainMenu::OnDestroy()
{
	Get()._bg->OnDestroy();
	Get()._startButton->OnDestroy();
	Get()._instrButton->OnDestroy();
	Get()._quitButton->OnDestroy();

	delete Get()._bg;
	delete Get()._startButton;
	delete Get()._instrButton;
	delete Get()._quitButton;

	Get()._bg = nullptr;
	Get()._startButton = nullptr;
	Get()._instrButton = nullptr;
	Get()._quitButton = nullptr;
}

void MainMenu::StartGame()
{
	Application::nextState = GameState::Game;
}

void MainMenu::Instructions()
{
	Application::nextState = GameState::Instructions;
}

void MainMenu::QuitToDesktop()
{
	Window::Close();
}
