#pragma once

#include "VisibleGameObject.h"

namespace mdu {

class PlayerPaddle: public VisibleGameObject 
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(const float elapsedTime);
	void Draw(sf::RenderWindow &renderWindow);

	float GetVelocity() const;

private:
	float m_velocity;
	float m_maxVelocity;
};

} //!< end namespace here