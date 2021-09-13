#ifndef MAPTOVECTORSORTER_H
#define MAPTOVECTORSORTER_H

#include <vector>

class MapToVectorSorter
{
public:
	/** */
	static std::vector<float> TransformAndSort(std::vector< std::vector<float> >& map);
};

#endif // MAPTOVECTORSORTER_H