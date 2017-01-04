// a-star-pathfinding-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.h"

using namespace Algorithms::Pathfinding;

TEST(MapClass, ShouldInitializeCompleteMap)
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

TEST(MapClass, ShouldInitializeIncompleteMap)
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

TEST(MapClass, ShouldInitializeEmptyMap)
{
	std::vector<std::string> lines;

	Map map(lines);

	ASSERT_EQ(0, map.SizeX());
	ASSERT_EQ(0, map.SizeY());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

