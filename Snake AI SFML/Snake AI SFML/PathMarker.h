#pragma once

#include "GridLocation.h"

class PathMarker
{
public:
	PathMarker(GridLocation _location, float _g, float _h, float _f, PathMarker* _parent);
	~PathMarker();

	bool Equals(PathMarker& _pathmarker) { return location.Equals(_pathmarker.location); }
	void Update(float _g, float _h, float _f, PathMarker* _parent);

	PathMarker* GetParent() { return parent; }
	GridLocation GetLocation() { return location; }
	float GetG() { return G; }
	float GetF() { return F; }

private:
	GridLocation location;
	float G;
	float H;
	float F;
	PathMarker* parent;
};

