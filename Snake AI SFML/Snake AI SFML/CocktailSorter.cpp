#include "CocktailSorter.h"

#include <Windows.h>
#include <iostream>

CocktailSorter::CocktailSorter(std::vector<PathMarker>& _listToSort) :
	sortingList(_listToSort),
	start(0),
	end((int)sortingList.size() - 1)
{
}

void CocktailSorter::Update()
{
	while(Sort())
	{
	}
}

bool CocktailSorter::Sort(void)
{
	bool stillSorting = false;
	int newStart = start;
	int newEnd = end;

	for(size_t i = start; i < end; i++) // Sorts from the lowest to the highest number (Start - End)
	{
		if(sortingList[i].GetF() > sortingList[i + 1].GetF())
		{
			PathMarker temp = sortingList[i];
			sortingList[i] = sortingList[i + 1];
			sortingList[i + 1] = temp;
			stillSorting = true;
			newEnd = (int)i;
		}
	}
	if(!stillSorting) // If the list is already sorted we can end the sorting
	{
		return stillSorting;
	}
	end = newEnd;
	for(size_t i = end; i > start; i--) // Sorts from the highest to the lowest number (End - Start)
	{
		if(sortingList[i].GetF() < sortingList[i - 1].GetF())
		{
			PathMarker temp = sortingList[i];
			sortingList[i] = sortingList[i - 1];
			sortingList[i - 1] = temp;
			stillSorting = true;
			newStart = (int)i;
		}
	}
	start = newStart;

	return stillSorting;
}