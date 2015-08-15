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
