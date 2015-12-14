#pragma once

#include "GameObjectManager.h"

namespace mdu {

class PlayerPaddle;

class Game 
{
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event GetInput();
	const static GameObjectManager& GetGameObjectManager();

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	typedef enum _GameState {
		Uninitialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	} GameState_e;

	static GameState_e m_gameState;
	static sf::RenderWindow m_mainWindow;
	static GameObjectManager m_gameObjectManager;
};

} //!< end namespace here