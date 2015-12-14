#include "stdafx.h"
#include "MainMenu.h"

namespace mdu {

MainMenu::MenuResult_e MainMenu::Show(sf::RenderWindow & window)
{
	//! Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("images/mainmenu.png");
	sf::Sprite sprite(texture);

	//! Setup clickable regions
	//! Play menu itme coordinates
	MenuItem_t playButton;
	playButton.rect.top = 145;
	playButton.rect.height = 235;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = Play;

	//! Exit menu item coordinates
	MenuItem_t exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.height = 177;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.action = Exit;

	m_menuItems.push_back(playButton);
	m_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult_e MainMenu::HandleClick(const int x, const int y)
{
	for (auto it = m_menuItems.begin(); it != m_menuItems.end(); ++it) {
		sf::Rect<int> menuItemRect = (*it).rect;
		if ((menuItemRect.height + menuItemRect.top) > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x) {
				return (*it).action;
		}
	}

	return MenuResult_e::Nothing;
}

MainMenu::MenuResult_e MainMenu::GetMenuResponse(sf::RenderWindow &window) 
{
	sf::Event menuEvent;
	while (true) {
		while (window.pollEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::EventType::MouseButtonPressed) {
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}

			if (menuEvent.type == sf::Event::EventType::Closed) {
				return Exit;
			}
		}
	}

	return MenuResult_e::Nothing;
}

} //!< end namespace here