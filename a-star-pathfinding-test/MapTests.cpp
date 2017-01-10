#include "stdafx.h"
#include "Map.h"

using namespace Algorithms::Pathfinding;

TEST(MapInitialization, ShouldInitializeCompleteMap)
{
	std::vector<std::string> lines =
	{
		"  *",
		" * "
	};

	Map map(lines);

	ASSERT_EQ(3, map.SizeX());
	ASSERT_EQ(2, map.SizeY());

	ASSERT_TRUE(map.IsWall(Point(2, 0)));
	ASSERT_TRUE(map.IsWall(Point(1, 1)));
	ASSERT_FALSE(map.IsWall(Point(0, 0)));
	ASSERT_FALSE(map.IsWall(Point(1, 0)));
	ASSERT_FALSE(map.IsWall(Point(0, 1)));
	ASSERT_FALSE(map.IsWall(Point(2, 1)));
}

TEST(MapInitialization, ShouldInitializeIncompleteMap)
{
	std::vector<std::string> lines =
	{
		"*",
		" *",
		""
	};

	Map map(lines);

	ASSERT_EQ(2, map.SizeX());
	ASSERT_EQ(3, map.SizeY());

	ASSERT_TRUE(map.IsWall(Point(0, 0)));
	ASSERT_TRUE(map.IsWall(Point(1, 1)));
	ASSERT_FALSE(map.IsWall(Point(1, 0)));
	ASSERT_FALSE(map.IsWall(Point(0, 1)));
	ASSERT_FALSE(map.IsWall(Point(0, 2)));
	ASSERT_FALSE(map.IsWall(Point(1, 2)));
}

TEST(MapInitialization, ShouldInitializeEmptyMap)
{
	std::vector<std::string> lines;

	Map map(lines);

	ASSERT_EQ(0, map.SizeX());
	ASSERT_EQ(0, map.SizeY());
}

TEST(Misc, ShouldCalculateDistanceCorrectly)
{
	ASSERT_EQ(0, Map::GetDistance(Point(3, 6), Point(3, 6)));
	ASSERT_EQ(1, Map::GetDistance(Point(4, 6), Point(3, 6)));
	ASSERT_EQ(1, Map::GetDistance(Point(2, 6), Point(3, 6)));
	ASSERT_EQ(1, Map::GetDistance(Point(3, 7), Point(3, 6)));
	ASSERT_EQ(1, Map::GetDistance(Point(3, 5), Point(3, 6)));
	ASSERT_EQ(9, Map::GetDistance(Point(3, 6), Point(-2, 2)));
}

