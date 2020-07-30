#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	Enemy() = default;
	virtual ~Enemy(){}

	virtual eType GetType() { return eType::ENEMY; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	void SetThrust(float thrust) { m_thrust = thrust; }
	void SetFireRate(float fireRate) { m_fireRate = fireRate; }
	void SetTarget(Actor* actor) { m_target = actor; }

	virtual void OnCollision(Actor* actor);

protected:
	float m_thrust{ 0.0f };
	float m_fireRate{ 1 };
	float m_fireTimer{ 0.0f };
	Actor* m_target{ nullptr };
};
