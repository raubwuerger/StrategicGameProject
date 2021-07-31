#pragma once

#include "IMapCreator.h"

class ModelMapRepository;

class ModelMapCreatorSaveGame : public IMapCreator
{
/** */
	virtual bool CreateMap();
/** */
	virtual ModelMapRepository* GetMap();

};