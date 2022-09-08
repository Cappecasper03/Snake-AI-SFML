#include "PathMarker.h"

PathMarker::PathMarker(GridLocation _location, float _g, float _h, float _f, PathMarker* _parent):
	location(_location),
	G(_g),
	H(_h),
	F(_f),
	parent(_parent),
	closed(false)
{
}

PathMarker::~PathMarker()
{
}

void PathMarker::Update(float _g, float _h, float _f, PathMarker* _parent)
{
	G = _g;
	H = _h;
	F = _f;
	parent = _parent;
}
