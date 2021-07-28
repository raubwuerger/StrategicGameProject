#include "stdafx.h"
#include "ModelMapConfig.h"

ModelMapConfig* ModelMapConfig::Instance = nullptr;

ModelMapConfig* ModelMapConfig::GetInstance()
{
	//TODO: Mit lock versehen
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelMapConfig;
	return Instance;
}

void ModelMapConfig::Release()
{
	delete Instance;
	Instance = nullptr;
}

ModelMapConfig::ModelMapConfig()
	: Rows(1),
	Cols(1)
{
}

ModelMapConfig::~ModelMapConfig()
{

}
