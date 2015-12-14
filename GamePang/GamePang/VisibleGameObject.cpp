#include "stdafx.h"
#include "VisibleGameObject.h"

namespace mdu {

VisibleGameObject::VisibleGameObject()
	: m_isLoaded(false)
	, m_filename("")
{
}

VisibleGameObject::~VisibleGameObject() {}

void VisibleGameObject::Load(const std::string &filename) 
{
	if (m_texture.loadFromFile(filename) == false) {
		m_filename = "";
		m_isLoaded = false;
	} else {
		m_filename = filename;
		m_sprite.setTexture(m_texture);
		m_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow &renderWindow)
{
	if (m_isLoaded) {
		renderWindow.draw(m_sprite);
	}
}

void VisibleGameObject::SetPosition(const float x, const float y)
{
	if (m_isLoaded) {
		m_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::Update(const float elapsedTime)
{
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (m_isLoaded) {
		return m_sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return m_sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return m_isLoaded;
}

float VisibleGameObject::GetHeight() const
{
	return m_sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return m_sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return m_sprite.getGlobalBounds();
}

} //!< end namespace here