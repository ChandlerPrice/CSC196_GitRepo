#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor
{
public:
	Player(){}
	virtual ~Player() {}

	virtual eType GetType() { return eType::PLAYER; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor);

	void GivePowerup(Actor* actor);
	void RemovePowerup(Player* player, float dt);
	int GetIsPowerup() { return m_powerupType; }

protected:
	nc::Vector2 m_velocity{ 0,0 };
	float m_thrust{ 150 };
	float m_fireRate{ 0.25f };
	float m_fireTimer{ 0.0f };
	float m_rotateRate{ 90 };
	float m_powerupLifetime{ 3 };
	int m_powerupType{ 0 };
};
