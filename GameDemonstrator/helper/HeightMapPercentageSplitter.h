#ifndef HEIGHTMAPCOLORMAPPER_H
#define HEIGHTMAPCOLORMAPPER_H

#include <vector>

class HeightMapPercentageSplitter
{
public:
	/** */
	HeightMapPercentageSplitter() {}
	/** */
	void ClearPercentageValue();
	/** Values between 1 and 100 are allowed */
	bool RegisterPercentageValue(int percentage);
	/** */
	std::map<int, std::vector<int> > CalculatePercentageValue(std::vector<int> values);
private:
	std::vector<int> PercentageValues;
};

#endif // HEIGHTMAPCOLORMAPPER_H