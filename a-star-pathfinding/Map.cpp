#include "stdafx.h"
#include "Map.h"

namespace Algorithms::Pathfinding
{
	Map::Map(const std::vector<std::string>& lines)
		: _sizeX(0), _sizeY(static_cast<int>(lines.size()))
	{
		for (int y = 0; y < _sizeY; y++)
		{
			std::string line = lines[y];
			int sizeX = static_cast<int>(line.size());

			if (_sizeX < sizeX)
			{
				_sizeX = sizeX;
			}

			for (int x = 0; x < sizeX; x++)
			{
				if (line[x] != ' ')
				{
					_walls.push_back(Point(x, y));
				}
			}
		}
	}

	int Map::SizeX() const
	{
		return _sizeX;
	}

	int Map::SizeY() const
	{
		return _sizeY;
	}

	bool Map::IsWall(const Point& position) const
	{
		return std::find(_walls.begin(), _walls.end(), position) != _walls.end();
	}

	bool Map::IsValidPath(const std::vector<Point>& path)
	{
		if (path.size() == 0)
		{
			std::cerr << "Path is empty.";
			return false;
		}

		std::set<long> passedPointHashes;

		for (int index = 0; index < path.size(); index++)
		{
			const Point& point = path[index];

			if (IsWall(point))
			{
				std::cerr << point << " is a wall.";
				return false;
			}

			if (point.X() < 0 || point.X() >= _sizeX || point.Y() < 0 || point.Y() >= _sizeY)
			{
				std::cerr << point << " is out of bounds. Map size: " << _sizeX << " x " << _sizeY;
				return false;
			}

			long pointHash = (point.X() << sizeof(int)) | point.Y();
			if (passedPointHashes.find(pointHash) != passedPointHashes.end())
			{
				std::cerr << "Path crosses itself at " << point;
				return false;
			}

			passedPointHashes.insert(pointHash);

			if (index > 0)
			{
				const Point& prevPoint = path[index - 1];
				if (GetDistance(point, prevPoint) != 1)
				{
					std::cerr << point << " is not adjacent to " << prevPoint;
					return false;
				}
			}
		}

		return true;
	}

	int Map::GetDistance(const Point& point1, const Point& point2)
	{
		return std::abs(point1.X() - point2.X()) + std::abs(point1.Y() - point2.Y());
	}
}