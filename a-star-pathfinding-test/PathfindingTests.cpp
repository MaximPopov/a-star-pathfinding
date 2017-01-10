#include "stdafx.h"
#include "Pathfinder.h"

using namespace Algorithms::Pathfinding;

void showPath(const Map& map, const std::vector<Point>& path);

TEST(Pathfinding, ShouldFindPathToOrigin)
{
	std::vector<std::string> lines =
	{
		"   ",
		" A ",
		"   "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto pPath = pathfinder.Find(map, Point(1, 1), Point(1, 1));

	ASSERT_TRUE(pPath != nullptr);
	ASSERT_EQ(1, pPath->size());
	ASSERT_EQ(Point(1, 1), pPath->at(0));

	showPath(map, *pPath);
}

TEST(Pathfinding, ShouldFindPathOnEmptyMap)
{
	std::vector<std::string> lines =
	{
		"  B",
		"   ",
		"A  "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto pPath = pathfinder.Find(map, Point(0, 2), Point(2, 0));

	ASSERT_TRUE(pPath != nullptr);
	ASSERT_TRUE(map.IsValidPath(*pPath));
	ASSERT_EQ(5, pPath->size());

	showPath(map, *pPath);
}

TEST(Pathfinding, ShouldFindPathAroundAWall)
{
	std::vector<std::string> lines =
	{
		"     ",
		"A  * ",
		"   *B",
		"     "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto pPath = pathfinder.Find(map, Point(0, 1), Point(4, 2));

	ASSERT_TRUE(pPath != nullptr);
	ASSERT_TRUE(map.IsValidPath(*pPath));
	ASSERT_EQ(8, pPath->size());

	showPath(map, *pPath);
}

TEST(Pathfinding, ShouldFindPathAroundDiagonalWall)
{
	std::vector<std::string> lines =
	{
		"     ",
		"   A*",
		"   *B",
		"     "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto pPath = pathfinder.Find(map, Point(3, 1), Point(4, 2));

	ASSERT_TRUE(pPath != nullptr);
	ASSERT_EQ(Point(3, 1), pPath->at(0));
	ASSERT_EQ(Point(2, 1), pPath->at(1));
	ASSERT_EQ(Point(2, 2), pPath->at(2));
	ASSERT_EQ(Point(2, 3), pPath->at(3));
	ASSERT_EQ(Point(3, 3), pPath->at(4));
	ASSERT_EQ(Point(4, 3), pPath->at(5));
	ASSERT_EQ(Point(4, 2), pPath->at(6));

	showPath(map, *pPath);
}

TEST(Pathfinding, ShouldNotFindPathIfCompletelyBlocked)
{
	std::vector<std::string> lines =
	{
		"  *  ",
		"   * ",
		"  A* ",
		"  *B "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto pPath = pathfinder.Find(map, Point(2, 2), Point(3, 3));

	ASSERT_TRUE(pPath == nullptr);
}

TEST(Pathfinding, ShouldFailIfOriginIsInvalid)
{
	std::vector<std::string> lines =
	{
		"     ",
		"   * ",
		"   * ",
		"     "
	};

	Map map(lines);

	Pathfinder pathfinder;
	ASSERT_THROW(pathfinder.Find(map, Point(3, 1), Point(4, 2)), std::exception);
}

TEST(Pathfinding, ShouldFailIfDestinationIsInvalid)
{
	std::vector<std::string> lines =
	{
		"     ",
		"   * ",
		"   * ",
		"     "
	};

	Map map(lines);

	Pathfinder pathfinder;
	ASSERT_THROW(pathfinder.Find(map, Point(0, 1), Point(4, 5)), std::exception);
}

TEST(Pathfinding, ShouldFindAWayInAHugeAssMaze)
{
	std::vector<std::string> lines =
	{
		"   *         *      *     *        **    ",
		"       * *    *  **  ** *   *         *  ",
		"   *   *     * *   *     **  **    ***   ",
		"   *  *   *     ** *  *   **  *  *    ** ",
		"**       *   ***   * *             * *   ",
		"      *   *     *         *  ***      * *",
		"** **  *  * **   * ***  * **    *   *    ",
		"      * *     *           *     **  ** **",
		"  ***     ***  ** * * * ***  * ****  *   ",
		" *   ** *        **  ***  *    *  * *  **",
		"   *  *  *  ** *     *  ****      * * *  ",
		"  **  *   * **  * * *  * *  **  ***      ",
		"  * *  *****      **  ** * *  **  * * * *",
		"  *          * *   * **     *  * * ** *  "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto pPath = pathfinder.Find(map, Point(0, 0), Point(map.SizeX() - 1, map.SizeY() - 1));

	ASSERT_TRUE(pPath != nullptr);
	showPath(map, *pPath);
}

void showPath(const Map& map, const std::vector<Point>& path)
{
	std::vector<std::string> lines;

	for (int y = 0; y < map.SizeY(); y++)
	{
		std::string line(map.SizeX(), ' ');
		for (int x = 0; x < map.SizeX(); x++)
		{
			if (map.IsWall(Point(x, y)))
			{
				line[x] = '*';
			}
		}
		lines.push_back(line);
	}

	char pathChar = '1';
	for (auto point : path)
	{
		lines[point.Y()][point.X()] = pathChar;

		pathChar++;
		if (pathChar > '9')
		{
			pathChar = '1';
		}
	}

	std::cout << std::string(map.SizeX() + 2, '-') << std::endl;
	for (auto line : lines)
	{
		std::cout << '|' << line << '|' << std::endl;
	}
	std::cout << std::string(map.SizeX() + 2, '-') << std::endl;
}