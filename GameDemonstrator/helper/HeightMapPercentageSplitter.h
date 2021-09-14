#ifndef HEIGHTMAPCOLORMAPPER_H
#define HEIGHTMAPCOLORMAPPER_H

#include <vector>
#include <map>

class HeightMapPercentageSplitter
{
public:
	/** */
	HeightMapPercentageSplitter();
	/** */
	void ClearPercentageValue();
	/** Values between 1 and 100 are allowed */
	bool RegisterPercentageValue(int percentage);
	/** */
	std::map<int, std::vector<float> > CalculatePercentageValue(std::vector<float> values);
private:
	std::vector<int> PercentageValues;
};

#endif // HEIGHTMAPCOLORMAPPER_H