#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"
#include "PlayerPaddle.h"

namespace mdu {

GameBall::GameBall()
	: m_velocity(230.0f)
	, m_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);
	float random_integer = (float)(std::rand() % 360 + 1);
	m_angle = random_integer;
}

GameBall::~GameBall()
{
}

void GameBall::Update(const float elapsedTime) //! Parameter is the time since last frame in seconds. VERY small number.
{
	m_elapsedTimeSinceStart += elapsedTime;

	//! Delay game from starting until 3 seconds have passed
	if (m_elapsedTimeSinceStart < 3.0f) {
		return;
	}

	float moveAmount = m_velocity  * elapsedTime;		
	float moveByX = LinearVelocityX(m_angle) * moveAmount;
	float moveByY = LinearVelocityY(m_angle) * moveAmount;
	
	//! collide with the left side of the screen
	if (GetPosition().x + moveByX <= 0 + GetWidth()/2 || GetPosition().x + GetHeight()/2 + moveByX >= SCREEN_WIDTH) {
		//! Ricochet!
		m_angle = 360.0f - m_angle;
		if(m_angle > 260.0f && m_angle < 280.0f) m_angle += 20.0f;
		if(m_angle > 80.0f && m_angle < 100.0f) m_angle += 20.0f;
		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	if (player1 != nullptr) {
		sf::Rect<float> p1BB = player1->GetBoundingRect();
	
		if (p1BB.intersects(GetBoundingRect())) { 
			m_angle =  360.0f - (m_angle - 180.0f);
			if (m_angle > 360.0f) {
				m_angle -= 360.0f;
			}	

			moveByY = -moveByY;

			//! Make sure ball isn't inside paddle
			if (GetBoundingRect().width > player1->GetBoundingRect().top) {
				SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth()/2 -1);
			}
		
			//! Now add "English" based on the players velocity.  
			float playerVelocity = player1->GetVelocity();
		
			if (playerVelocity < 0) {
				//! moving left
				m_angle -= 20.0f;
				if(m_angle < 0 ) m_angle = 360.0f - m_angle;
			} else if (playerVelocity > 0) {
				m_angle += 20.0f;
				if (m_angle > 360.0f) {
					m_angle = m_angle - 360.0f;
				}
			}

			m_velocity += 5.0f;
		}

		if (GetPosition().y - GetHeight()/2 <= 0) {
			m_angle =  180 - m_angle;
			moveByY = -moveByY;
		}

		if (GetPosition().y + GetHeight()/2 + moveByY >= SCREEN_HEIGHT) {
			//! move to middle of the screen for now and randomize angle
			GetSprite().setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
			m_angle = (float)(std::rand() % 360) + 1;
			m_velocity = 230.0f;
			m_elapsedTimeSinceStart = 0.0f;
		}

		GetSprite().move(moveByX,moveByY);
	}
}

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
    if (angle < 0) {
		angle = 360 + angle;
	}

	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
    if (angle < 0) {
		angle = 360 + angle;
	}
	
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}

} //!< end namespace here