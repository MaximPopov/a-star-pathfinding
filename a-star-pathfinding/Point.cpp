#include "stdafx.h"
#include "Point.h"

namespace Algorithms::Pathfinding
{
	std::ostream& operator<<(std::ostream& os, const Point& point)
	{
		os << '(' << point._x << ',' << point._y << ')';
		return os;
	}
}