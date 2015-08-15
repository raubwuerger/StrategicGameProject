#pragma once
class CTerrainType
{
public:
	/** */
	CTerrainType();
	/** */
	~CTerrainType();
private:
//	friend class CTerrainTypeFactory;
	int			m_Id;
	QString		m_Name;
	QString		m_PicturePath;
	int			m_Oil;
	int			m_Timber;
	int			m_MovementModifier;
	int			m_DefenseModifier;
};

