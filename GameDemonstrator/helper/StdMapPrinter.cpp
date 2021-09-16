#include "stdafx.h"
#include "StdMapPrinter.h"
#include <fstream>
#include <iterator>

void StdMapPrinter::PrintMap(const std::vector< std::vector<float> >& map)
{
	if (true == map.empty())
	{
		return;
	}

	std::vector<std::string> printMap;

	unsigned int rows = map.size();
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		std::string rowString;
		std::vector<float> currenRow = map.at(rowIndex);
		unsigned int cols = currenRow.size();
		for (int colIndex = 0; colIndex < cols; colIndex++)
		{
			rowString += std::to_string(currenRow.at(colIndex));
			rowString += "; ";
		}
		printMap.push_back(rowString);
	}

	std::ofstream output_file("./mapPrint.txt");
	std::ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(printMap.begin(), printMap.end(), output_iterator);
}
