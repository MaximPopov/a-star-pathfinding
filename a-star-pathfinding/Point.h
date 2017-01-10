#pragma once

namespace Algorithms::Pathfinding
{
	class Point
	{
		friend std::ostream& operator<<(std::ostream& os, const Point& point);

	public:
		//Point() : Point(0, 0) {}

		Point(int x, int y)
			: _x(x), _y(y)
		{
		}

		int X() const { return _x; }
		int Y() const { return _y; }

		inline bool operator==(const Point& other) const
		{
			return _x == other._x && _y == other._y;
		}

	private:

		int _x;
		int _y;
	};
}