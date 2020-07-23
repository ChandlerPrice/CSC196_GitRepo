#include "pch.h"
#include "Shape.h"
#include "Math/Matrix22.h"
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

			//get color
			stream >> m_color;

			//get num of points
			std::string line;
			std::getline(stream, line);
			size_t size;
			size = stoi(line);

			//read points
			for (size_t i = 0; i < size; i++)
			{
				Vector2 v;
				stream >> v;
				m_points.push_back(v);
			}

			stream.close();
		}

		// get radius
		m_radius = 0;
		for (size_t i = 0; i < m_points.size(); i++)
		{
			nc::Vector2 p1 = m_points[i];
			float length = p1.Length();
			if (length > m_radius) m_radius = length;
		}

		return sucess;
	}

	void Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
	{
		graphics.SetColor(this->GetColor());

		nc::Matrix33 mxs;
		mxs.Scale(scale);

		nc::Matrix33 mxr;
		mxr.Rotate(angle);

		nc::Matrix33 mxt;
		mxt.Translate(position);

		nc::Matrix33 mx = mxs * mxr * mxt;

		for (size_t i = 0; i < this->m_points.size() - 1; i++)
		{
			nc::Vector2 p1 = this->m_points[i];
			nc::Vector2 p2 = this->m_points[i + 1];

			//Transform
			p1 = p1 * mx;
			p2 = p2 * mx;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transorm)
	{
		graphics.SetColor(this->GetColor());

		for (size_t i = 0; i < this->m_points.size() - 1; i++)
		{
			nc::Vector2 p1 = this->m_points[i];
			nc::Vector2 p2 = this->m_points[i + 1];

			//Transform
			p1 = p1 * transorm.matrix;
			p2 = p2 * transorm.matrix;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}
