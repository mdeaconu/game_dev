#pragma once

#include "VisibleGameObject.h"

namespace mdu {

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(const std::string &name, VisibleGameObject *gameObject);
	void Remove(const std::string &name);
	int GetObjectCount() const;
	VisibleGameObject* Get(const std::string &name) const;

	void DrawAll(sf::RenderWindow & renderWindow);
	void UpdateAll();

private:
	std::map<std::string, VisibleGameObject*> m_gameObjects;
	sf::Clock clock;
};

} //!< end namespace here