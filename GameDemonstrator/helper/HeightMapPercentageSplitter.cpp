#include "stdafx.h"
#include "HeightMapPercentageSplitter.h"

void HeightMapPercentageSplitter::ClearPercentageValue()
{
	PercentageValues.clear();
}

bool HeightMapPercentageSplitter::RegisterPercentageValue(int percentage)
{
	if (percentage <= 0)
	{
		return false;
	}
	if (percentage > 100)
	{
		return false;
	}
	PercentageValues.push_back(percentage);
}

std::map<int, std::vector<int> > HeightMapPercentageSplitter::CalculatePercentageValue(std::vector<int> values)
{
	std::sort(values.begin(), values.end(), std::less<float>());
	std::sort(PercentageValues.begin(), PercentageValues.end(), std::less<int>());

	int valueCount = values.size();
	std::map<int, std::vector<int> > splitterMap;

	int lastPercentageValue = 0;
	std::vector<int>::iterator percentageIterator = PercentageValues.begin();
	while (percentageIterator != PercentageValues.end())
	{
//		splitterMap.insert(values.[lastPercentageValue], values[percentageIterator]);
	}
	return splitterMap;
}

