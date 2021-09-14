//#include "stdafx.h"
#include "HeightMapPercentageSplitter.h"
#include <map>
#include <algorithm>

HeightMapPercentageSplitter::HeightMapPercentageSplitter()
{

}

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
	if ( std::find(PercentageValues.begin(), PercentageValues.end(), percentage) != PercentageValues.end() )
	{
		return false;
	}
	PercentageValues.push_back(percentage);
	return true;
}

std::map<int, std::vector<float> > HeightMapPercentageSplitter::CalculatePercentageValue(std::vector<float> values)
{
	std::sort(values.begin(), values.end(), std::less<float>());
	std::sort(PercentageValues.begin(), PercentageValues.end(), std::less<int>());

	int valueCount = values.size();

	std::map<int, std::vector<float> > splitterMap;
	int lastPercentageValue = 0;
	std::vector<int>::iterator percentageIterator = PercentageValues.begin();
	while (percentageIterator != PercentageValues.end())
	{
		std::vector<float> sub(&values[lastPercentageValue], &values[*percentageIterator]);
		splitterMap.insert(std::make_pair(*percentageIterator, sub));
	}
	return splitterMap;
}

