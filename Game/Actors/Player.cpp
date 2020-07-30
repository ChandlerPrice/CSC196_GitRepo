#include "Player.h"
#include "Object/Scene.h"
#include <fstream>
#include <Math\Math.h>
#include "Graphics/ParticleSystem.h"
#include "../Game.h"
#include "Projectile.h"
#include "Powerup.h"

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

	if (m_powerupType != 0)
	{
		RemovePowerup(m_scene->GetActor<Player>(), dt);
	}

	m_transform.Update();
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE)
	{
		Game* game = m_scene->GetGame();
		game->AddLife(-1);
		if (game->GetLives() <= 0)
		{
			RemovePowerup(m_scene->GetActor<Player>(), 5);
			m_scene->GetGame()->SetState(Game::eState::GAME_OVER);
		}
	}
	else if (actor->GetType() == eType::POWERUP)
	{
		GivePowerup(actor);
	}
}

void Player::GivePowerup(Actor* actor)
{
	Powerup* powerup = new Powerup;
	powerup = dynamic_cast<Powerup*>(actor);
	switch (powerup->GetPowerup())
	{
	case Powerup::ePowerup::SLOW:
		m_scene->SetDtMultiplier(0.25f);
		m_powerupType = 1;
		break;
	case Powerup::ePowerup::BOMB:
		m_scene->RemoveAllActorOfType(Actor::eType::ENEMY);
		m_scene->RemoveAllActorOfType(Actor::eType::PROJECTILE);
		break;
	case Powerup::ePowerup::HEALTH:
		m_scene->GetGame()->AddLife(1);
		break;
	case Powerup::ePowerup::SPEED:
		m_scene->GetActor<Player>()->m_thrust = 1200;
		m_powerupType = 2;
		break;
	case Powerup::ePowerup::NONE:
		m_scene->SetDtMultiplier(1);
		break;
	default:
		m_scene->SetDtMultiplier(50);
		break;
	}
}

void Player::RemovePowerup(Player* player, float dt)
{
	player->m_powerupLifetime -= dt;
	if (player->m_powerupLifetime <= 0)
	{
		switch (player->GetIsPowerup())
		{
		case 0:
			m_scene->SetDtMultiplier(1);
			m_scene->GetActor<Player>()->m_thrust = 800;
			break;
		case 1:
			m_scene->SetDtMultiplier(1);
			break;
		case 2:
			m_scene->GetActor<Player>()->m_thrust = 800;
			break;
		default:
			m_scene->SetDtMultiplier(50);
			break;
		}
		player->m_powerupType = 0;
		player->m_powerupLifetime = 3;
	}
}

