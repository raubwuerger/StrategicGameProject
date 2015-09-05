#pragma once

class CTerrainType;

/** Kartenteil im Speicher */
class CVirtualMapItem
{
public:
	CVirtualMapItem();
	~CVirtualMapItem();
private:
	QPoint			m_CenterPoint;
	int				m_Row;
	int				m_Col;
	CTerrainType	*m_Type;
};

