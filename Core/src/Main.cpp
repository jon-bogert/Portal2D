#include "Pch.h"
#include "Window.h"
#include "Game.h"
#include "AssetManager.h"
#include "MainMenu.h"
#include "InstructionsScreen.h"
#include "Physics.h"

// ==== CONTROL DEFINES ====

//#define USE_WINMAIN // Uncomment to build as Windows Desktop Application
#define ESC_TO_CLOSE true // Window will close with escape key -> Good for Debugging

// =========================

#ifdef USE_WINMAIN
#include <windows.h>
#endif

namespace Application
{
    extern GameState nextState = GameState::Game; // TODO - Change to Main Menu // States Enum in Structs.h
}

#ifdef USE_WINMAIN
int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
#else
int main(int argc, char* argv[])
#endif
{
    srand(time(NULL));
    GameState currentState = Application::nextState;

    AssetManager::Load();
    sf::Clock deltaClock;


    while (Window::GetIsOpen())
    {
        //START
        switch (currentState)
        {
        case GameState::MainMenu:
            MainMenu::Start();
            break;
        case GameState::Game:
            Game::Start();
            break;
        case GameState::Instructions:
            InstructionsScreen::Start();
            break;
        }

        deltaClock.restart();
        while (Window::GetIsOpen() && currentState == Application::nextState)
        {
            const float deltaTime = deltaClock.restart().asSeconds();
            xe::InputSystem::Update(Window::UnWrap(), deltaTime , ESC_TO_CLOSE);

            //UPDATE
            switch (currentState)
            {
            case GameState::MainMenu:
                MainMenu::Update(deltaTime);
                break;
            case GameState::Game:
                Game::Update(deltaTime);
                break;
            case GameState::Instructions:
                InstructionsScreen::Update(deltaTime);
                break;
            }

            switch (currentState)
            {
            case GameState::Game:
                Game::LateUpdate(deltaTime);
                break;
            }

            Physics::TimeStep(deltaTime, 6, 2);

            switch (currentState)
            {
            case GameState::Game:
                Game::PostUpdate(deltaTime);
                break;
            }

            //DRAW
            Window::Clear();
            switch (currentState)
            {
            case GameState::MainMenu:
                MainMenu::Draw();
                break;
            case GameState::Game:
                Game::Draw();
                break;
            case GameState::Instructions:
                InstructionsScreen::Draw();
                break;
            }
            Window::Display();
        }

        //ON_DESTROY
        switch (currentState)
        {
        case GameState::MainMenu:
            MainMenu::OnDestroy();
            break;
        case GameState::Game:
            Game::OnDestroy();
            break;
        case GameState::Instructions:
            InstructionsScreen::OnDestroy();
            break;
        }
        currentState = Application::nextState;
    }
	return 0;
}