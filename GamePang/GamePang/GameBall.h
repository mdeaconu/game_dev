#pragma once

#include "VisibleGameObject.h"

namespace mdu {

class GameBall: public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();
	void Update(const float);

private:
	float m_velocity;
	float m_angle;
	float m_elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
};

} //!< end namespace here