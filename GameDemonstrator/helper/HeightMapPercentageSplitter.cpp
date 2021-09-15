#include "stdafx.h"
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
	if (true == PercentageValues.empty())
	{
		return std::map<int, std::vector<float> >();
	}

	if (PercentageValues.size() >= values.size())
	{
		return std::map<int, std::vector<float> >();
	}

	std::sort(values.begin(), values.end(), std::less<float>());
	std::sort(PercentageValues.begin(), PercentageValues.end(), std::less<int>());

	float percentValue = 100.0;
	float onePercentOfValues = static_cast<float>(values.size()) / percentValue;

	std::map<int, std::vector<float> > splitterMap;
	unsigned int lastIndex = 0;
	for (std::vector<int>::iterator it = std::begin(PercentageValues); it != std::end(PercentageValues); ++it)
	{
		float curentIndex = *it * onePercentOfValues;
		std::vector<float> sub(&values[lastIndex], &values[static_cast<int>(curentIndex)]);
		splitterMap.insert(std::make_pair(*it, sub));
		lastIndex = static_cast<int>(curentIndex);
	}



	if (lastIndex < values.size())
	{
		unsigned int vectorSize = values.size();
		std::vector<float> sub(&values[lastIndex], &values[--vectorSize]);
		sub.push_back(values[vectorSize]);
		int lastIndexOfValue = *(PercentageValues.end() - 1);
		splitterMap.insert(std::make_pair(++lastIndexOfValue, sub));
	}

	return splitterMap;
}

