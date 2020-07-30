#include "Enemy.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "../Game.h"
#include <fstream>
#include "Powerup.h"

bool Enemy::Load(const std::string& filename)
{
    bool success = false;

    std::ifstream stream(filename);
    if (stream.is_open())
    {
        success = true;

        // load the base actor members
        Actor::Load(stream);

        stream >> m_thrust;

        stream.close();
    }

    return success;
}

void Enemy::Update(float dt)
{
	m_fireTimer += dt;
	if (m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		Projectile* projectile = new Projectile;
		projectile->Load("Projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle - 29.85f;
		g_audioSystem.PlayAudio("Shoot");
		m_scene->AddActor(projectile);
	}

	nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	nc::Vector2 enemyVelocity = direction.Normalized() * m_thrust;
	m_transform.position += enemyVelocity * dt;
	m_transform.angle = std::atan2(direction.y, direction.x);

    m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PLAYER)
	{
		m_destroy = true;
		//m_scene->RemoveActor(actor);

		m_scene->GetGame()->AddPoints(100);

		nc::Color colors[] = { nc::Color::red, nc::Color::green, nc::Color::red };
		nc::Color color = colors[rand() % 3];

		g_audioSystem.PlayAudio("Explosion");
		g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);


		Powerup* powerup = new Powerup;
		powerup->Load(powerup->SetRandomPowerup());
		powerup->GetTransform().position = m_transform.position - rand() % 1000;
		powerup->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(powerup);
	}
}
