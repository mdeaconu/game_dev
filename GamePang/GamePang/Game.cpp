#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayerPaddle.h"
#include "GameBall.h"

namespace mdu {

Game::GameState_e Game::m_gameState = Uninitialized;
sf::RenderWindow Game::m_mainWindow;
GameObjectManager Game::m_gameObjectManager;

void Game::Start()
{
	if (m_gameState != Uninitialized) {
		return;
	}

	m_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");

	//! create obj
	PlayerPaddle *player1 = new PlayerPaddle();
	player1->SetPosition((SCREEN_HEIGHT/2), 700);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2)-15);

	m_gameObjectManager.Add("Paddle1", player1);
	m_gameObjectManager.Add("Ball", ball);

	m_gameState = Game::ShowingSplash;

	while (!IsExiting()) {
		GameLoop();
	}

	m_mainWindow.close();
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::m_gameObjectManager;
}

bool Game::IsExiting()
{
	if (m_gameState == Game::Exiting) {
		return true;
	}
	return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return m_mainWindow;
}

const sf::Event Game::GetInput()
{
	sf::Event currentEvent;
	m_mainWindow.pollEvent(currentEvent);

	return currentEvent;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	m_mainWindow.pollEvent(currentEvent);

	switch (m_gameState) {
	case Game::ShowingMenu: {
		ShowMenu();
    } break;
	case Game::ShowingSplash: {
		ShowSplashScreen();
    } break;
	case Game::Playing: {
		m_mainWindow.clear(sf::Color(0, 0, 0));
		m_gameObjectManager.UpdateAll();
		m_gameObjectManager.DrawAll(m_mainWindow);
		m_mainWindow.display();

		if (currentEvent.type == sf::Event::Closed) {
			m_gameState = Game::Exiting;
		}

		if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape) {
			ShowMenu();
		}
    } break;
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(m_mainWindow);
	m_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult_e result = mainMenu.Show(m_mainWindow);

	switch (result) {
	case MainMenu::Exit: {
		m_gameState = Game::Exiting;
    } break;
	case MainMenu::Play: {
		m_gameState = Game::Playing;
	} break;
	}
}

} //end namespace