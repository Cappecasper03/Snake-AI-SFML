#pragma once

#include "PathMarker.h"

#include <vector>

class CocktailSorter
{
public:
	CocktailSorter(std::vector<PathMarker>& _listToSort);

	void Update(void); // Calls the sorting, printing and calls the sort check once

private:
	bool Sort(void); // Sorts the list

	std::vector<PathMarker>& sortingList;
	int start; // Used to know where the start of the unsorted numbers are
	int end; // Used to know where the end of the unsorted numbers are
};