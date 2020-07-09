#include "pch.h"
#include "Shape.h"
#include "Math/Vector2.h"
#include <fstream>
#include <string>

namespace nc
{
	bool Shape::Load(std::string& filename)
	{
		bool sucess = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			sucess = true;

			stream >> m_color;

			//read points
			while (!stream.eof())
			{
				Vector2 point;
				stream >> point;

				if (!stream.eof())
				{
					m_points.push_back(point);
				}
			}

			stream.close();
		}

		return sucess;
	}

	void Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
	{
		graphics.SetColor(this->GetColor());

		for (size_t i = 0; i < this->m_points.size() - 1; i++)
		{
			nc::Vector2 p1 = this->m_points[i];
			nc::Vector2 p2 = this->m_points[i + 1];

			//Transform
			p1 = p1 * scale;
			p2 = p2 * scale;

			//Rotate
			p1 = nc::Vector2::Rotate(p1, angle);
			p2 = nc::Vector2::Rotate(p2, angle);

			//Translate
			p1 = p1 + position;
			p2 = p2 + position;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transorm)
	{
		Draw(graphics, transorm.position, transorm.scale, transorm.angle);
	}
}
