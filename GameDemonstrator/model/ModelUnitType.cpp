#include "stdafx.h"
#include "ModelUnitType.h"

ModelUnitType::ModelUnitType(int id)
	:Id(id)
{
}

int ModelUnitType::GetId() const
{
	return Id;
}

const QImage* ModelUnitType::GetImage() const
{
	return Image;
}

const QString& ModelUnitType::GetName() const
{
	return Name;
}

const QString& ModelUnitType::GetPicturePath() const
{
	return PicturePath;
}

void ModelUnitType::SetImage(const QImage* image)
{
	Image = image;
}
