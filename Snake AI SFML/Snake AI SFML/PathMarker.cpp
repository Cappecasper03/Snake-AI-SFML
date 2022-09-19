#include "PathMarker.h"

PathMarker::PathMarker(GridLocation _location) :
	location(_location),
	G(0),
	H(0),
	F(0),
	parent(nullptr)
{
}

PathMarker::PathMarker(GridLocation _location, GameArea& _area) :
	location(_location),
	G(0),
	H(0),
	F(0),
	parent(nullptr)
{
	SetMarker(_location, _area);
}

PathMarker::PathMarker(GridLocation _location, float _g, float _h, float _f, PathMarker* _parent) :
	location(_location),
	G(_g),
	H(_h),
	F(_f),
	parent(_parent),
	marker()
{
}

void PathMarker::Update(float _g, float _h, float _f, PathMarker* _parent)
{
	G = _g;
	H = _h;
	F = _f;
	parent = _parent;
}

void PathMarker::SetPositionByOrigo(sf::Vector2f _origoPosition)
{
	marker.setPosition(sf::Vector2f(_origoPosition.x - (marker.getSize().x / 2), _origoPosition.y - (marker.getSize().y / 2)));
}

void PathMarker::SetPositionByGridLocation(GridLocation _location, GameArea& _area)
{
	float x = _area.GetWalls().getPosition().x + _area.GetTileSize() * _location.GetX() - _area.GetTileSize() / 2;
	float y = _area.GetGridLines()[0].getSize().y - (_area.GetWalls().getPosition().y + _area.GetTileSize() * _location.GetY() - _area.GetTileSize() / 2);
	SetPositionByOrigo(sf::Vector2f(x, y));
}

void PathMarker::SetMarker(GridLocation _location, GameArea& _area)
{
	marker.setFillColor(sf::Color::Magenta);
	marker.setSize(sf::Vector2f(_area.GetTileSize() * .2f, _area.GetTileSize() * .2f));

	SetPositionByGridLocation(_location, _area);
}