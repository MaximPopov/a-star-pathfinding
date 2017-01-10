#include "stdafx.h"
#include "Pathfinder.h"

namespace Algorithms::Pathfinding
{
	class OpenListItem
	{
	public:
		OpenListItem(const Point& position, int gScore, int hScore, std::shared_ptr<OpenListItem> parent)
			: _position(position)
			, _gScore(gScore)
			, _hScore(hScore)
			, _parent(parent)
		{
		}

		const Point& GetPosition() const { return _position; }
		int GetGScore() const { return _gScore; }
		int GetHScore() const { return _hScore; }
		int GetFScore() const { return _gScore + _hScore; }
		std::shared_ptr<OpenListItem> GetParent() const { return _parent; }

		void UpdatePath(int gScore, std::shared_ptr<OpenListItem> parent)
		{ 
			_ASSERT(gScore < _gScore);
			_ASSERT(parent != nullptr);

			_gScore = gScore;
			_parent = parent;
		}

	private:
		Point _position;
		int _gScore;
		int _hScore;
		std::shared_ptr<OpenListItem> _parent;
	};

	void CollectAdjacentPositions(const Point& position, std::vector<Point>& adjacentPositions)
	{
		adjacentPositions.push_back(Point(position.X() - 1, position.Y()));
		adjacentPositions.push_back(Point(position.X(), position.Y() - 1));
		adjacentPositions.push_back(Point(position.X() + 1, position.Y()));
		adjacentPositions.push_back(Point(position.X(), position.Y() + 1));
	}

	std::unique_ptr<std::vector<Point>> Pathfinder::Find(const Map& map, const Point& originPosition, const Point& destinationPosition)
	{
		if (map.IsOutOfBounds(originPosition) || map.IsWall(originPosition))
		{
			throw std::exception("Origin position is invalid.");
		}
		if (map.IsOutOfBounds(destinationPosition) || map.IsWall(destinationPosition))
		{
			throw std::exception("Destination position is invalid.");
		}

		std::vector<Point> closedList;
		std::vector<std::shared_ptr<OpenListItem>> openList = { std::make_shared<OpenListItem>(originPosition, 0, Map::GetDistance(originPosition, destinationPosition), nullptr) };

		do
		{
			auto minIt = openList.begin();
			for (auto it = minIt + 1; it != openList.end(); ++it)
			{
				if ((*it)->GetFScore() < (*minIt)->GetFScore())
				{
					minIt = it;
				}
			}

			std::shared_ptr<OpenListItem> pCurrentItem = *minIt;
			const Point& currentPosition = pCurrentItem->GetPosition();
			closedList.push_back(currentPosition);
			openList.erase(minIt);

			if (currentPosition == destinationPosition)
			{
				std::vector<Point> path;
				
				do
				{
					path.insert(path.begin(), pCurrentItem->GetPosition());
					pCurrentItem = pCurrentItem->GetParent();
				} while (pCurrentItem != nullptr);

				return std::make_unique<std::vector<Point>>(path);
			}

			std::vector<Point> adjacentPositions;
			CollectAdjacentPositions(currentPosition, adjacentPositions);
			for (auto position : adjacentPositions)
			{
				if (map.IsOutOfBounds(position) || map.IsWall(position) || std::find(closedList.begin(), closedList.end(), position) != closedList.end())
				{
					continue;
				}

				int gScore = pCurrentItem->GetGScore() + 1;
				int hScore = Map::GetDistance(position, destinationPosition);

				auto it = std::find_if(openList.begin(), openList.end(), [&position](const std::shared_ptr<OpenListItem>& pItem) { return pItem->GetPosition() == position; });
				if (it != openList.end())
				{
					if (gScore < (*it)->GetGScore())
					{
						(*it)->UpdatePath(gScore, pCurrentItem);
					}
				}
				else
				{
					openList.insert(openList.begin(), std::make_shared<OpenListItem>(position, gScore, hScore, pCurrentItem));
				}
			}
		} 
		while (openList.size() > 0);

		return nullptr;
	}
}