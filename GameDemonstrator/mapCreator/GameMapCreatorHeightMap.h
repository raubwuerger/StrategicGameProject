#ifndef GAMEMAPCREATORHEIGHTMAP_H
#define GAMEMAPCREATORHEIGHTMAP_H

#include "IGameMapCreator.h"
#include "GameMapCreatorHeightMapData.h"

class GameMapTile;
class ModelTerrainType;

class GameMapCreatorHeightMap : public IGameMapCreator
{
public:
	/** */
	GameMapCreatorHeightMap();
	/** */
	void SetMapCreationData(GameMapCreatorHeightMapData mapCreationData);
	/** */
	bool CreateMap(GameMapCreatorHeightMapData mapCreationData);
public:
	/** */
	bool CreateMap() override;
private:
	/** */
	bool GenerateHeightMap(std::vector< std::vector<float> >& heightMapVector );
	/** */
	void GenerateDefaultMapCreationData();
	/** */
	bool CreateGameMapTiles(std::vector< std::vector<float> >& heightMapVector);
	/** */
	GameMapTile* CreateGameMapTile(unsigned int row, unsigned int col);
	/** */
	const ModelTerrainType* GetModelTerrainType(float value) const;
private:
	GameMapCreatorHeightMapData MapCreationData;
};

#endif // GAMEMAPCREATORHEIGHTMAP_H