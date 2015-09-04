#include "stdafx.h"
#include "TerrainTypeEditor.h"
#include "MapEventManager.h"
#include "TerrainTypeRepository.h"
#include "MapEventManager.h"
#include "TerrainType.h"

CTerrainTypeEditor::CTerrainTypeEditor(QObject *parent)
	: QObject(parent),
	m_ActiveTerrainType(nullptr),
	m_TerrainTypeRepository(nullptr),
	m_MapEventManager(nullptr)
{

}

CTerrainTypeEditor::~CTerrainTypeEditor()
{

}

void CTerrainTypeEditor::ActivateTerrainType( int terrainTypeId )
{
	m_ActiveTerrainType = m_TerrainTypeRepository->FindTerrainTypeById( terrainTypeId );
}

#include "MapViewHexItem.h"
void CTerrainTypeEditor::ChangeTerrainTypeHexItem( int row, int col )
{
	Q_ASSERT(m_TerrainTypeRepository);
	Q_ASSERT(m_MapEventManager);
	if( m_ActiveTerrainType == nullptr )
	{
		return;
	}

	MapViewHexItem *item = m_MapEventManager->FindItemByIndexNonConst( row, col );
	if( item == nullptr )
	{
		return;
	}
	item->SetTerrainImage( m_ActiveTerrainType->GetImage() );
}
