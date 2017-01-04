#pragma once

#include "Point.h"

namespace Algorithms::Pathfinding
{
	class Map
	{
	public:
		Map(const std::vector<std::string>& lines);

		bool IsWall(const Point& position) const;
		int SizeX() const;
		int SizeY() const;

	private:
		std::vector<Point> _walls;
		int _sizeX;
		int _sizeY;
	};
}