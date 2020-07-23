#include "Player.h"
#include "Object/Scene.h"
#include <fstream>
#include <Math\Math.h>
#include "Graphics/ParticleSystem.h"
#include "Projectile.h"

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// load the base actor members
		Actor::Load(stream);

		stream >> m_thrust;
		stream >> m_rotateRate;

		stream.close();
	}

	return success;
}

void Player::Update(float dt)
{
	if (isDead)
	{

	}
	else
	{
		nc::Vector2 force;
		if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
		force = nc::Vector2::Rotate(force, m_transform.angle);
		//force = force + nc::Vector2{ 0, 200 };

		m_velocity = m_velocity * 0.98f + (force * dt);

		m_transform.position += (m_velocity * dt);

		if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (dt * nc::DegreesToRadians(m_rotateRate)); }
		if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (dt * nc::DegreesToRadians(m_rotateRate)); }

		m_transform.position = nc::Clamp(m_transform.position, { 10,10 }, { 790, 590 });

		if (force.LengthSqr() > 0)
		{
			g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::green, 1, 100, 200);
		}

		m_transform.Update();
	}
	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;
	//direction.Normalize();

	//if (player.GetTransform().position.x > 800) player.GetTransform().position.x = 0;
	//if (player.GetTransform().position.x < 0) player.GetTransform().position.x = 800;
	//if (player.GetTransform().position.y > 600) player.GetTransform().position.y = 0;
	//if (player.GetTransform().position.y < 0) player.GetTransform().position.y = 600;

	//player.GetTransform().position.x = nc::Clamp(player.GetTransform().position.x, 10.0f, 790.0f);
	//player.GetTransform().position.y = nc::Clamp(player.GetTransform().position.y, 10.0f, 590.0f);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE)
	{
		isDead = true;
		//m_scene->RemoveActor(actor);
	}
}
