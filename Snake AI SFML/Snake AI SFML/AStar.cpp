#include "AStar.h"
#include "CocktailSorter.h"

#include <math.h>

AStar::AStar(GridLocation _startNode, GridLocation _goalNode) :
	open(),
	closed(),
	startNode(_startNode, 0, 0, 0, nullptr),
	goalNode(_goalNode, 0, 0, 0, nullptr),
	lastPos(startNode),
	stillSearching(true)
{
	open.push_back(startNode);
}

AStar::~AStar()
{
}

void AStar::Search(PathMarker* _playerNode, GameArea _area)
{
	if(_playerNode->Equals(goalNode)) // Found the best path
	{
		stillSearching = false;
		return;
	}

	for(GridLocation dir : directions)
	{
		GridLocation neighbourNode = dir.Add(_playerNode->GetLocation());

		int currentSnake = 0;
		//Todo Clone the snake move

		// If the 'neighbourNode' is outside of the game area
		if(neighbourNode.GetX() <= 0 || neighbourNode.GetX() > _area.GetGridSize() ||
			neighbourNode.GetY() <= 0 || neighbourNode.GetY() > _area.GetGridSize())
		{
			continue;
		}

		if(IsClosed(neighbourNode))
			continue;

		bool hitsItself = false;
		//Todo Checking if the 'neighbourNode' is a part of the snake

		if(hitsItself)
			continue;

		// Distance between 'startNode' and 'neighbourNode'
		float G = abs(_playerNode->GetLocation().GetX() - neighbourNode.GetX()) + abs(_playerNode->GetLocation().GetY() - neighbourNode.GetY()) + _playerNode->GetG();
		// Distance between 'neighbourNode' and 'goalNode'
		float H = abs(neighbourNode.GetX() - goalNode.GetLocation().GetX()) + abs(neighbourNode.GetY() - goalNode.GetLocation().GetY());
		// The sum of G and H which also is the distance between the 'startNode' and the 'goalNode'
		float F = G + H;

		if(!UpdateMarker(neighbourNode, G, H, F, _playerNode))
			open.push_back(PathMarker(neighbourNode, G, H, F, _playerNode));
	}

	CocktailSorter sorter(open);
	sorter.Update();

	PathMarker pm = open.front();
	closed.push_back(pm);
	open.erase(open.begin());

	lastPos = pm;
}

bool AStar::UpdateMarker(GridLocation _position, float _g, float _h, float _f, PathMarker* _parent)
{
	for(PathMarker marker : open)
	{
		if(marker.GetLocation().Equals(_position))
		{
			marker.Update(_g, _h, _f, _parent);
			return true;
		}
	}

	return false;
}

bool AStar::IsClosed(GridLocation _location)
{
	for(PathMarker marker : closed)
	{
		if(marker.GetLocation().Equals(_location))
			return true;
	}

	return false;
}

void AStar::GetPath()
{
	PathMarker* path = &lastPos;

	while(!path && !path->Equals(goalNode))
	{
		//Todo Get Path Code

		path = path->GetParent();
	}
}
