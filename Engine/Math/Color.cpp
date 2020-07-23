#include "pch.h"
#include "Color.h"


namespace nc
{
	const Color Color::white{ 1,1,1 };
	const Color Color::red{ 1,0,0 };
	const Color Color::green{ 0,1,0 };
	const Color Color::blue{ 0,0,1 };
	const Color Color::yellow{ 1,1,0 };
	const Color Color::magenta{ 1,0,1 };
	const Color Color::cyan{ 0,1,1 };

	std::istream& operator>>(std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		{
			std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			c.r = std::stof(cr);

			line = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);

			std::string cg = line.substr(0, line.find(","));
			c.g = std::stof(cg);

			std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			c.b = std::stof(cb);
		}

		return stream;
	}
}

