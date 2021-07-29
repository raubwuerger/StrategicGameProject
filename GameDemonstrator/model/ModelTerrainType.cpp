#include "stdafx.h"
#include "ModelTerrainType.h"

ModelTerrainType::ModelTerrainType( int id )
	: Id(id),
	Oil(0),
	Timber(0),
	MovementModifier(0),
	DefenseModifier(0),
	Infrastructure(0),
	Image(nullptr)
{
}

ModelTerrainType::~ModelTerrainType()
{
	delete Image;
}

int ModelTerrainType::GetId() const
{
	return Id;
}

QColor ModelTerrainType::InterpolateColorByType() const
{
	switch( Id )
	{
	case 1:
		return QColor(Qt::green);
	case 2:
		return QColor(Qt::darkGreen);
	case 3:
		return QColor(Qt::blue);
	case 4:
		return QColor(205,170,125);
	case 5:
		return QColor(Qt::gray);
	default:
		return QColor(Qt::white);
	}
}

const QString& ModelTerrainType::GetName() const
{
	return Name;
}

void ModelTerrainType::SetImage( const QImage * val )
{
	Image = val;
}

const QImage * ModelTerrainType::GetImage() const
{
	return Image;
}
