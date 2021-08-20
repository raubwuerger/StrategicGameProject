#include "stdafx.h"
#include "ModelCityType.h"

ModelCityType::ModelCityType(int id)
	: Id(id)
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
