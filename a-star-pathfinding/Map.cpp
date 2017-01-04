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
}