#include "stdafx.h"
#include "ModelOwnerType.h"

ModelOwnerType::ModelOwnerType( int id )
	: Id(id),
	Human(true),
	Color(Qt::lightGray)
{
}

ModelOwnerType::~ModelOwnerType()
{
}

const QString& ModelOwnerType::GetName() const
{
	return Name;
}

int ModelOwnerType::GetId() const
{
	return Id;
}

QString ModelOwnerType::toString() const
{
	return QObject::tr("ModelOwnerType - Id: %1, Name: %2, PictureName: %3").arg(QString::number(Id)).arg(Name).arg(PictureName);
}

const QColor& ModelOwnerType::GetColor() const
{
	return Color;
}

bool ModelOwnerType::operator==(const ModelOwnerType& rhs) const
{
	return this->Id == rhs.Id;
}

bool ModelOwnerType::GetHuman() const
{
	return Human;
}
