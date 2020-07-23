#pragma once
#include "Object/Actor.h"

class Projectile : public nc::Actor
{
public:
	Projectile() = default;
	virtual ~Projectile() {}

	virtual eType GetType() { return eType::PROJECTILE; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	void SetThrust(float thrust) { m_thrust = thrust; }

	virtual void OnCollision(Actor* actor);

protected:
	float m_thrust{ 0 };
	float m_lifetime{ 3 };
};
