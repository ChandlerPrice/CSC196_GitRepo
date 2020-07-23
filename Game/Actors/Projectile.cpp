#include "Projectile.h"
#include "Math/Vector2.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>
#include <Math\Math.h>

bool Projectile::Load(const std::string& filename)
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

void Projectile::Update(float dt)
{
    m_lifetime -= dt;
    m_destroy = (m_lifetime <= 0);

    nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
    nc::Vector2 velocity = direction * m_thrust;
    m_transform.position = m_transform.position + velocity * dt;

    g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::red, 0.25f, 100, 200);

    m_transform.Update();
}

void Projectile::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::PLAYER)
    {
        m_destroy = true;
        //m_scene->RemoveActor(actor);

        nc::Color colors[] = { nc::Color::yellow, nc::Color::red, nc::Color::yellow };
        nc::Color color = colors[rand() % 3];

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
    }
}