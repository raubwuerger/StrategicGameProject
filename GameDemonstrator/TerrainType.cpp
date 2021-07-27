#include "stdafx.h"
#include "TerrainType.h"

TerrainType::TerrainType( int id )
	: Id(id),
	Oil(0),
	Timber(0),
	MovementModifier(0),
	DefenseModifier(0),
	Infrastructure(0),
	Image(nullptr)
{
}

TerrainType::~TerrainType()
{
	delete Image;
}

int TerrainType::GetId() const
{
	return Id;
}

QColor TerrainType::InterpolateColorByType() const
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

const QString& TerrainType::GetName() const
{
	return Name;
}

void TerrainType::SetImage( const QImage * val )
{
	Image = val;
}

const QImage * TerrainType::GetImage() const
{
	return Image;
}
