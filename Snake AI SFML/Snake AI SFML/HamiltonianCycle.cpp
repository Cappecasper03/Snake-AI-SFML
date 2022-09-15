#include "HamiltonianCycle.h"
#include "AStar.h"

HamiltonianCycle::HamiltonianCycle(std::vector<SnakePart> _snake, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones)
{
	AStar aStarTail(_snake[0].GetLocation(), _snake[_snake.size() - 1].GetLocation(), _area, _snakeClones);

	moves = aStarTail.GetMoves();
	ExtendPath(moves, _snake, _area);
}

void HamiltonianCycle::ExtendPath(std::vector<PathMarker>& _moves, std::vector<SnakePart>& _snakeClone, GameArea& _area)
{
	Directions directions;

	std::vector<PathMarker> movesCopy;
	movesCopy.push_back(PathMarker(_snakeClone[0].GetLocation(), _area));
	for(int i = (int)_moves.size() - 1; i >= 0; i--)
	{
		movesCopy.push_back(_moves[i]);
	}

	for(int i = 1; i < movesCopy.size();)
	{
		bool extended = false;

		GridLocation dir = movesCopy[i - 1].GetLocation().GetDirectionTo(movesCopy[i].GetLocation());
		GridLocation current = movesCopy[i].GetLocation();

		if(dir.GetX() != 0)
		{
			GridLocation currentUp = movesCopy[i - 1].GetLocation().Add(directions.Up);
			bool curUp = true;
			GridLocation currentDown = movesCopy[i - 1].GetLocation().Add(directions.Down);
			bool curDown = true;
			GridLocation nextUp = movesCopy[i].GetLocation().Add(directions.Up);
			bool nUp = true;
			GridLocation nextDown = movesCopy[i].GetLocation().Add(directions.Down);
			bool nDown = true;

			for(PathMarker marker : movesCopy)
			{
				if(marker.GetLocation().Equals(currentUp))
					curUp = false;
				if(marker.GetLocation().Equals(currentDown))
					curDown = false;
				if(marker.GetLocation().Equals(nextUp))
					nUp = false;
				if(marker.GetLocation().Equals(nextDown))
					nDown = false;
			}

			for(int j = 1; j < _snakeClone.size() - 1; j++)
			{
				if(_snakeClone[j].GetLocation().Equals(currentUp))
					curUp = false;
				if(_snakeClone[j].GetLocation().Equals(currentDown))
					curDown = false;
				if(_snakeClone[j].GetLocation().Equals(nextUp))
					nUp = false;
				if(_snakeClone[j].GetLocation().Equals(nextDown))
					nDown = false;
			}

			if(currentUp.GetX() <= 0 || currentUp.GetX() > _area.GetGridSize() || currentUp.GetY() <= 0 || currentUp.GetY() > _area.GetGridSize())
				curUp = false;
			if(currentDown.GetX() <= 0 || currentDown.GetX() > _area.GetGridSize() || currentDown.GetY() <= 0 || currentDown.GetY() > _area.GetGridSize())
				curDown = false;
			if(nextUp.GetX() <= 0 || nextUp.GetX() > _area.GetGridSize() || nextUp.GetY() <= 0 || nextUp.GetY() > _area.GetGridSize())
				nUp = false;
			if(nextDown.GetX() <= 0 || nextDown.GetX() > _area.GetGridSize() || nextDown.GetY() <= 0 || nextDown.GetY() > _area.GetGridSize())
				nDown = false;

			if(curUp && nUp)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentUp.Add(dir.Add(directions.Down)), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentUp.Add(dir), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentUp, _area));
				extended = true;
			}
			else if(curDown && nDown)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.Add(dir.Add(directions.Up)), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.Add(dir), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown, _area));
				extended = true;
			}
		}
		else if(dir.GetY() != 0)
		{
			GridLocation currentRight = movesCopy[i - 1].GetLocation().Add(directions.Right);
			bool curRight = true;
			GridLocation currentLeft = movesCopy[i - 1].GetLocation().Add(directions.Left);
			bool curLeft = true;
			GridLocation nextRight = movesCopy[i].GetLocation().Add(directions.Right);
			bool nRight = true;
			GridLocation nextLeft = movesCopy[i].GetLocation().Add(directions.Left);
			bool nLeft = true;

			for(PathMarker marker : movesCopy)
			{
				if(marker.GetLocation().Equals(currentRight))
					curRight = false;
				if(marker.GetLocation().Equals(currentLeft))
					curLeft = false;
				if(marker.GetLocation().Equals(nextRight))
					nRight = false;
				if(marker.GetLocation().Equals(nextLeft))
					nLeft = false;
			}

			for(int j = 1; j < _snakeClone.size() - 1; j++)
			{
				if(_snakeClone[j].GetLocation().Equals(currentRight))
					curRight = false;
				if(_snakeClone[j].GetLocation().Equals(currentLeft))
					curLeft = false;
				if(_snakeClone[j].GetLocation().Equals(nextRight))
					nRight = false;
				if(_snakeClone[j].GetLocation().Equals(nextLeft))
					nLeft = false;
			}

			if(currentRight.GetX() <= 0 || currentRight.GetX() > _area.GetGridSize() || currentRight.GetY() <= 0 || currentRight.GetY() > _area.GetGridSize())
				curRight = false;
			if(currentLeft.GetX() <= 0 || currentLeft.GetX() > _area.GetGridSize() || currentLeft.GetY() <= 0 || currentLeft.GetY() > _area.GetGridSize())
				curLeft = false;
			if(nextRight.GetX() <= 0 || nextRight.GetX() > _area.GetGridSize() || nextRight.GetY() <= 0 || nextRight.GetY() > _area.GetGridSize())
				nRight = false;
			if(nextLeft.GetX() <= 0 || nextLeft.GetX() > _area.GetGridSize() || nextLeft.GetY() <= 0 || nextLeft.GetY() > _area.GetGridSize())
				nLeft = false;

			if(curRight && nRight)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentRight.Add(dir.Add(directions.Left)), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentRight.Add(dir), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentRight, _area));
				extended = true;
			}
			else if(curLeft && nLeft)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentLeft.Add(dir.Add(directions.Right)), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentLeft.Add(dir), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentLeft, _area));
				extended = true;
			}
		}

		if(!extended)
			i++;
	}

	moves.clear();
	for(int i = 1; i < movesCopy.size(); i++)
	{
		moves.insert(moves.begin(), movesCopy[i]);
	}
}