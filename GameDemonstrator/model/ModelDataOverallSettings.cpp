#include "stdafx.h"
#include "ModelDataOverallSettings.h"

ModelDataOverallSettings* ModelDataOverallSettings::Instance = nullptr;

ModelDataOverallSettings* ModelDataOverallSettings::GetInstance()
{
	//TODO: Mit semaphore oder mutex absichern!
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new ModelDataOverallSettings;
	return Instance;
}

ModelMapConfig* ModelDataOverallSettings::GetGameMapConfig()
{
	return ModelMapConfig::GetInstance();
}