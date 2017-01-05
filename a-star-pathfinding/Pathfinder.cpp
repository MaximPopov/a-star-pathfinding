#include "stdafx.h"
#include "Pathfinder.h"

namespace Algorithms::Pathfinding
{
	std::unique_ptr<std::vector<Point>> Pathfinder::Find(const Map& map, const Point& origin, const Point& destination)
	{
		std::vector<Point> path;

		return std::make_unique<std::vector<Point>>(path);
	}
}