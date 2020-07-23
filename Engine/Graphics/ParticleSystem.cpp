#include "pch.h"
#include "Math/Random.h"
#include "Math/Math.h"
#include "ParticleSystem.h"

nc::ParticleSystem g_particleSystem;

void nc::ParticleSystem::Startup()
{
    m_size = 3000;
    m_particles = new Particle[m_size];
}

void nc::ParticleSystem::Shutdown()
{
    delete[] m_particles;
}

void nc::ParticleSystem::Update(float dt)
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (p->isActive)
        {
            p->lifetime = p->lifetime - dt;
            p->isActive = (p->lifetime > 0);

            p->prevPosition = p->position;
            p->position = p->position + (p->velocity * dt);
            p->velocity = p->velocity * p->damping;
        }
    }
}

void nc::ParticleSystem::Draw(Core::Graphics& graphics)
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (p->isActive)
        {
            graphics.SetColor(p->color);
            graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
        }
    }
}

void nc::ParticleSystem::Create(const Vector2& position, 
                                float angle, 
                                float angleRange, 
                                size_t count, 
                                const Color color, 
                                float lifetime, 
                                float speedMin, 
                                float speedMax)
{
    for (size_t i = 0; i < count; i++)
    {
        Particle* p = GetFreeParticle();
        if (p)
        {
            p->isActive = true;
            p->lifetime = lifetime;
            p->position = position;
            p->prevPosition = position;
            p->color = color;
            
            float angleRandom = DegreesToRadians(random(-angleRange, angleRange));
            Vector2 direction = Vector2::Rotate(Vector2::forward, angle + angleRandom);
            p->velocity = direction * random(speedMin, speedMax);
        }
    }
}

nc::Particle* nc::ParticleSystem::GetFreeParticle()
{
    Particle* freeParticle{ nullptr };
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (!p->isActive)
        {
            freeParticle = p;
            break;
        }
    }

    return freeParticle;
}
