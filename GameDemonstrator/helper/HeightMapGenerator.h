#ifndef HEIGHTMAPGENERATOR_H
#define HEIGHTMAPGENERATOR_H

class GameMapCreatorHeightMapData;

class HeightMapGenerator
{
public:
	/** */
	bool GenerateHeightMap(const GameMapCreatorHeightMapData& mapCreationData, std::vector< std::vector<float> >& heightMapVector );
};

#endif // HEIGHTMAPGENERATOR_H