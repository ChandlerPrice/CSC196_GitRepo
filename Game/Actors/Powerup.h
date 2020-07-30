#pragma once
#include "Object/Actor.h"
#include <random>

class Powerup : public nc::Actor
{
public:
	enum class ePowerup
	{
		SLOW,
		BOMB,
		HEALTH,
		SPEED,
		NONE
	};
public:
	Powerup() = default;
	virtual ~Powerup() {}

	virtual eType GetType() { return eType::POWERUP; }

	virtual ePowerup GetPowerup() { return m_powerup; }
	virtual std::string SetRandomPowerup();

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor);

protected:
	float m_lifetime{ 4 };
	float m_thrust{ 0 };
	ePowerup m_powerup{ ePowerup::SLOW };
};