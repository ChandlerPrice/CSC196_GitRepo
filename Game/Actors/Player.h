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

protected:
	nc::Vector2 m_velocity{ 0,0 };
	float m_thrust{ 150 };
	float m_fireRate{ 0.25f };
	float m_fireTimer{ 0.0f };
	float m_rotateRate{ 90 };
	bool isDead{ false };
};
