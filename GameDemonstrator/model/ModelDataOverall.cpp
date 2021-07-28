#include "stdafx.h"
#include "ModelDataOverall.h"
#include "GameMapConfig.h"

ModelDataOverall::ModelDataOverall()
{
}

ModelDataOverall::~ModelDataOverall()
{
}

void ModelDataOverall::Init()
{
}

void ModelDataOverall::Release()
{
}

GameMapConfig* ModelDataOverall::GetGameMapConfig()
{
	return GameMapConfig::GetInstance();
}
