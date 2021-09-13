#include "stdafx.h"
#include "MapToVectorSorter.h"
#include <algorithm>
#include <functional>

std::vector<float> MapToVectorSorter::TransformAndSort(std::vector< std::vector<float> >& map)
{
	std::vector<float> unsortedVector;
	for (int rowIndex = 0; rowIndex < map.size(); rowIndex++)
	{
		for (int colIndex = 0; colIndex < map[rowIndex].size(); colIndex++)
		{
			unsortedVector.push_back(map[rowIndex][colIndex]);
		}
	}
	std::sort(unsortedVector.begin(), unsortedVector.end(), std::less<float>());
	return unsortedVector;
}
