#pragma once

#include <list>

namespace mdu {

class MainMenu 
{
public:
	typedef enum _MenuResult {
		Nothing,
		Exit,
		Play
	} MenuResult_e;

	typedef struct _MenuItem {
		sf::Rect<int> rect;
		MenuResult_e action;
	} MenuItem_t;

	MenuResult_e Show(sf::RenderWindow &window);

private:
	MenuResult_e GetMenuResponse(sf::RenderWindow & window);
	MenuResult_e HandleClick(const int, const int);
	std::list<MenuItem_t> m_menuItems;
};

} //!< end namespace here