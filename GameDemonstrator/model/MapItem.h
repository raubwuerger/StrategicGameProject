#pragma once

class CTerrainType;

namespace GDModel
{
/** Kartenteil im Speicher */
class CMapItem
{
public:
	CMapItem();
	~CMapItem();
private:
	QPoint			m_CenterPoint;
	int				m_Row;
	int				m_Col;
	CTerrainType	*m_Type;
};


}
