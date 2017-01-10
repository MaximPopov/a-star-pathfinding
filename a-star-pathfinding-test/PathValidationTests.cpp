#include "stdafx.h"
#include "Pathfinder.h"

using namespace Algorithms::Pathfinding;

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

TEST(PathValidation, ShouldInvalidateOutOfBoundsPath)
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

