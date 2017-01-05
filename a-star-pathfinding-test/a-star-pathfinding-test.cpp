// a-star-pathfinding-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Pathfinder.h"

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

TEST(PathValidation, ShouldValidateCorrectPath)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	std::vector<Point> path = { Point(1, 1), Point(2, 1), Point(2, 2), Point(1, 2), Point(0, 2), Point(0, 1), Point(0, 0) };

	ASSERT_TRUE(map.IsValidPath(path));
}

TEST(PathValidation, ShouldInvalidateEmptyPath)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	std::vector<Point> path;

	ASSERT_FALSE(map.IsValidPath(path));
}

TEST(PathValidation, ShouldInvalidateNonContiguousPath)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	std::vector<Point> path = { Point(0, 0), Point(1, 0), Point(1, 2), Point(2, 2) };

	ASSERT_FALSE(map.IsValidPath(path));
}

TEST(PathValidation, ShouldInvalidateOutOfBounsPath)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	std::vector<Point> path = { Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0) };

	ASSERT_FALSE(map.IsValidPath(path));
}

TEST(PathValidation, ShouldInvalidateIntersectingPath)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	std::vector<Point> path = { Point(0, 1), Point(1, 1), Point(2, 1), Point(2, 2), Point(1, 2), Point(1, 1), Point(1, 0) };

	ASSERT_FALSE(map.IsValidPath(path));
}

TEST(PathValidation, ShouldInvalidatePathThatCrossesAWall)
{
	std::vector<std::string> lines =
	{
		" * ",
		" * ",
		"   "
	};

	Map map(lines);

	std::vector<Point> path = { Point(2, 1), Point(1, 1) };

	ASSERT_FALSE(map.IsValidPath(path));
}

TEST(Pathfinding, ShouldFindPathToOrigin)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto path = pathfinder.Find(map, Point(1, 1), Point(1, 1));

	ASSERT_TRUE(path != nullptr);
	ASSERT_EQ(1, path->size());
	ASSERT_EQ(Point(1, 1), path->at(0));
}

TEST(Pathfinding, ShouldFindShortestPathOnEmptyMap)
{
	std::vector<std::string> lines =
	{
		"   ",
		"   ",
		"   "
	};

	Map map(lines);

	Pathfinder pathfinder;
	auto path = pathfinder.Find(map, Point(0, 2), Point(2, 0));

	ASSERT_TRUE(path != nullptr);
	ASSERT_EQ(5, path->size());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
