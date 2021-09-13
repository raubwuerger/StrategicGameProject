#ifndef GAMEMAPCREATORHEIGHTMAP_H
#define GAMEMAPCREATORHEIGHTMAP_H

#include "IGameMapCreator.h"
#include "GameMapCreatorHeightMapData.h"

class GameMapCreatorHeightMap : public IGameMapCreator
{
public:
	/** */
	GameMapCreatorHeightMap();
	/** */
	void SetMapCreationData(GameMapCreatorHeightMapData mapCreationData);
public:
	/** */
	bool CreateMap() override;
private:
	/** */
	bool GenerateHeightMap();
private:
	GameMapCreatorHeightMapData MapCreationData;
};

#endif // GAMEMAPCREATORHEIGHTMAP_H