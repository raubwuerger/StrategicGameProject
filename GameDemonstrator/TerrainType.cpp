#include "stdafx.h"
#include "TerrainType.h"

CTerrainType::CTerrainType( int id )
	: m_Id(id),
	m_Oil(0),
	m_Timber(0),
	m_MovementModifier(0),
	m_DefenseModifier(0),
	m_Infrastructure(0)
{
}

CTerrainType::~CTerrainType()
{
}

int CTerrainType::GetId() const
{
	return m_Id;
}

QColor CTerrainType::InterpolateColorByType() const
{
	switch( m_Id )
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
	}
}

const QString& CTerrainType::GetName() const
{
	return m_Name;
}
