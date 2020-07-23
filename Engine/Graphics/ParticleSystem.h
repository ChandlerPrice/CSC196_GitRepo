#pragma once
#include "Particle.h"
#include "core.h"

namespace nc
{
	class ParticleSystem
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position, float angle, float angleRange, size_t count, const Color color, float lifetime, float speedMin, float speedMax);

	protected:
		Particle* GetFreeParticle();

	protected:
		Particle* m_particles;
		size_t m_size;
	};
}

extern nc::ParticleSystem g_particleSystem;