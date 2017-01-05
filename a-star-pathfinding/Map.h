#pragma once

#include "Point.h"

namespace Algorithms::Pathfinding
{
	class Map
	{
	public:
		Map(const std::vector<std::string>& lines);

		int SizeX() const;
		int SizeY() const;
		bool IsWall(const Point& position) const;
		bool IsValidPosition(const Point& position);
		bool IsValidPath(const std::vector<Point>& path);

		static int GetDistance(const Point& point1, const Point& point2);

	private:
		std::vector<Point> _walls;
		int _sizeX;
		int _sizeY;
	};
}