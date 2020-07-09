#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace nc
{
	bool Actor::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;
			stream >> m_transform;

			std::string shapename;
			stream >> shapename;
			m_shape.Load(shapename);

			stream.close();
		}

		return success;
	}

	void Actor::Update(float dt)
	{
		// nothing
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}
}
