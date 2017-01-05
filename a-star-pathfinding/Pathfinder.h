#pragma once

#include "stdafx.h"
#include "Map.h"

namespace Algorithms::Pathfinding
{
	class Pathfinder
	{
	public:
		std::unique_ptr<std::vector<Point>> Find(const Map& map, const Point& origin, const Point& destination);
	};
}