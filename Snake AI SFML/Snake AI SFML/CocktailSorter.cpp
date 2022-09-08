#include "CocktailSorter.h"

#include <Windows.h>
#include <iostream>
#include <chrono>

CocktailSorter::CocktailSorter(std::vector<PathMarker>& _listToSort) :
	sortingList(_listToSort),
	start(0),
	end(sortingList.size() - 1)
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

	for(int i = start; i < end; i++) // Sorts from the highest to the lowest number (Start - End)
	{
		if(sortingList[i].GetF() > sortingList[i + 1].GetF())
		{
			PathMarker temp = sortingList[i];
			sortingList[i] = sortingList[i + 1];
			sortingList[i + 1] = temp;
			stillSorting = true;
			newEnd = i;
		}
	}
	if(!stillSorting) // If the list is already sorted we can end the sorting
	{
		return stillSorting;
	}
	end = newEnd;
	for(int i = end; i > start; i--) // Sorts from the lowest to the highest number (End - Start)
	{
		if(sortingList[i].GetF() < sortingList[i - 1].GetF())
		{
			PathMarker temp = sortingList[i];
			sortingList[i] = sortingList[i - 1];
			sortingList[i - 1] = temp;
			stillSorting = true;
			newStart = i;
		}
	}
	start = newStart;

	return stillSorting;
}