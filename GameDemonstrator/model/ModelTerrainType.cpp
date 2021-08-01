#include "stdafx.h"
#include "ModelTerrainType.h"

ModelTerrainType::ModelTerrainType( int id )
	: Id(id),
	Infrastructure(0),
	Oil(0),
	Timber(0),
	Stone(0),
	MovementModifier(0),
	DefenseModifier(0),
	AttackModifier(0),
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

QString ModelTerrainType::toString() const
{
	return QObject::tr("ModelTerrainType - Id: %1, Name: %2, PicturePath: %3, Infrastructure: %4, Oil: %5, Timber: %6, Stone: %7, MovementModifier: %8, AttackModifier: %9" )
		.arg(QString::number(Id))
		.arg(Name)
		.arg(PicturePath)
		.arg(QString::number(Infrastructure))
		.arg(QString::number(Oil))
		.arg(QString::number(Timber))
		.arg(QString::number(Stone))
		.arg(QString::number(MovementModifier))
		.arg(QString::number(DefenseModifier))
		.arg(QString::number(AttackModifier));
}

const QString& ModelTerrainType::GetPicturePath() const
{
	return PicturePath;
}
