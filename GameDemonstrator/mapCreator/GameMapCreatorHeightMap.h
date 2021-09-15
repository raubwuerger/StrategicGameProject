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
	/** */
	void InitHeightValueUpperBorders(std::vector< std::vector<float> >& heightMapVector );
	/** */
	void DefaultInitHeightValueUpperBorders();
	/** */
	void SetPercentageValue( const std::vector<float>& values, float& upperPercentageValue );
private:
	GameMapCreatorHeightMapData MapCreationData;
	float	HeightValueUpperBorderOcean;
	float	HeightValueUpperBorderPlain;
	float	HeightValueUpperBorderWood;
	float	HeightValueUpperBorderHill;
	float	HeightValueUpperBorderMountain;
};

#endif // GAMEMAPCREATORHEIGHTMAP_H