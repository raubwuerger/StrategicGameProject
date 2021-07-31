#pragma once

#include "IMapCreator.h"

class ModelMapRepository;

class MapCreatorSaveGame : public IMapCreator
{
/** */
	virtual bool CreateMap();
/** */
	virtual ModelMapRepository* GetMap();

};