#include "stdafx.h"
#include "ModelOwnerType.h"

ModelOwnerType::ModelOwnerType( int id )
	: Id(id),
	Human(true),
	Color(Qt::green)
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
	return QObject::tr("ModelOwnerType - Id: %1, Name: %2, PicturePath: %3").arg(QString::number(Id)).arg(Name).arg(PicturePath);
}

bool ModelOwnerType::GetHuman() const
{
	return Human;
}
