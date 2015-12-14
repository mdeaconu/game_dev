#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

namespace mdu {

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(m_gameObjects.begin(), 
		m_gameObjects.end(), 
		[&](const std::pair<std::string, VisibleGameObject*> &pair) { 
			delete pair.second; 
		}
	);

	//! clean up also the list
	m_gameObjects.clear();
}

void GameObjectManager::Add(const std::string &name, VisibleGameObject *gameObject)
{
	m_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(const std::string &name)
{
	auto results = m_gameObjects.find(name);

	if (results != m_gameObjects.end()) {
		delete results->second;
		m_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(const std::string &name) const
{
	auto results = m_gameObjects.find(name);
	if (results == m_gameObjects.end()) {
		return nullptr;
	}

	return results->second;
}

int GameObjectManager::GetObjectCount() const 
{
	return m_gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow &renderWindow)
{
	std::for_each(m_gameObjects.begin(),
		m_gameObjects.end(),
		[&](const std::pair<std::string, VisibleGameObject*> &pair) {
			pair.second->Draw(renderWindow);
		}
	);
}

void GameObjectManager::UpdateAll()
{
	float timeDelta = clock.restart().asSeconds();
	std::for_each(m_gameObjects.begin(),
		m_gameObjects.end(),
		[&](const std::pair<std::string, VisibleGameObject*> &pair) {
			pair.second->Update(timeDelta);
		}
	);
}

} //!< end namespace here