#pragma once

class CTerrainType;
class COwnerType;

namespace GDModel
{
/** Kartenteil im Speicher */
class CMapItem
{
public:
	/** */
	CMapItem( int row, int col );
	/** */
	~CMapItem();
private:
	QPoint			m_CenterPoint;
	int				m_Row;
	int				m_Col;
	CTerrainType	*m_Type;
	COwnerType		*m_Owner;
};


}
