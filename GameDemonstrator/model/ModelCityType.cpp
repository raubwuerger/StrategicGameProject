#include <stdafx.h>
#include "ModelCityType.h"

ModelCityType::ModelCityType(int id)
	: Id(id),
	Name(NOT_INITIALIZED_STRING),
	PictureName(NOT_INITIALIZED_STRING),
	Image(nullptr),
	Efficiency(NOT_INITIALIZED_INT),
	SpezializedUnitType(NOT_INITIALIZED_INT),
	DefenceValue(NOT_INITIALIZED_INT),
	BaseProductionPoints(NOT_INITIALIZED_INT)
{

}

int ModelCityType::GetId() const
{
	return Id;
}

const QString ModelCityType::toString() const
{
	return QObject::tr("ModelCityType - Id: %1, Name: %2, PictureName: %3").arg(QString::number(Id)).arg(Name).arg(PictureName);
}

bool ModelCityType::IsPlaceableOnTerrainType(int terrainTypeId) const
{
	return PlacableTerrainTypes.contains(terrainTypeId);
}
