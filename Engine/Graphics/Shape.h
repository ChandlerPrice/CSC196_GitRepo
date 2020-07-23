#pragma once
#include "core.h"
#include "../Math/Color.h"
#include "../Math/Vector2.h"
#include "../Math/Transform.h"
#include <vector>
#include <string>

namespace nc
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) { m_color = color; m_points = points; }

		bool Load(std::string& filename);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle);
		void Draw(Core::Graphics& graphics, const Transform& transform);

		void SetColor(Color color) { m_color = color; }
		const Color& GetColor() const { return m_color; }

		float GetRadius() { return m_radius; }

	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
		float m_radius;
	};
}


