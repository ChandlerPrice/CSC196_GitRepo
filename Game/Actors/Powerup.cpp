#include "Powerup.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
#include <fstream>
#include <Math\Math.h>
#include "Graphics/Shape.h"
#include <random>
#include <iostream>
#include <string>

std::string Powerup::SetRandomPowerup()
{
    m_powerup = static_cast<ePowerup>(rand() % 4);
    std::string fileName = "Powerup1.txt";
    switch (m_powerup)
    {
    case Powerup::ePowerup::SLOW:
        fileName = "Powerup1.txt";
        break;
    case Powerup::ePowerup::BOMB:
        fileName = "Powerup2.txt";
        break;
    case Powerup::ePowerup::HEALTH:
        fileName = "Powerup3.txt";
        break;
    case Powerup::ePowerup::SPEED:
        fileName = "Powerup4.txt";
        break;
    case Powerup::ePowerup::NONE:
        break;
    default:
        break;
    }
    return fileName;
}

bool Powerup::Load(const std::string& filename)
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

void Powerup::Update(float dt)
{
    m_lifetime -= dt;
    m_destroy = (m_lifetime <= 0);

    nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
    nc::Vector2 velocity = direction * m_thrust;
    m_thrust = m_thrust / 2;
    m_transform.position = m_transform.position + velocity * dt;

    g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::magenta, 0.25f, 100, 200);

    m_transform.Update();
}

void Powerup::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::PLAYER)
    {
        m_destroy = true;
        //m_scene->RemoveActor(actor);

        nc::Color colors[] = { nc::Color::magenta, nc::Color::green, nc::Color::magenta };
        nc::Color color = colors[rand() % 3];

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
    }
}
