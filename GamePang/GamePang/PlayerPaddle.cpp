#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

namespace mdu {

PlayerPaddle::PlayerPaddle()
	: m_velocity(0.0f)
	, m_maxVelocity(1200.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow & renderWindow)
{
	VisibleGameObject::Draw(renderWindow);
}

float PlayerPaddle::GetVelocity() const
{
	return m_velocity;
}

void PlayerPaddle::Update(const float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_velocity -= 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_velocity += 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_velocity = 0.0f;
	}

	if (m_velocity > m_maxVelocity) {
		m_velocity = m_maxVelocity;
	}
	if (m_velocity < -m_maxVelocity) {
		m_velocity = -m_maxVelocity;
	}

	const sf::Vector2f &pos = this->GetPosition();
	if (pos.x < GetSprite().getLocalBounds().width/2 
		|| pos.x > (SCREEN_WIDTH - GetSprite().getLocalBounds().width/2)) {
		m_velocity = -m_velocity;
	}

	GetSprite().move(m_velocity * elapsedTime, 0);
}

} //!< end namespace here