#pragma once
class CTerrainType
{
public:
	/** */
	CTerrainType( int id );
	/** */
	~CTerrainType();
	/** Get m_Id */	
	int GetId() const;
	/** Wird später entfernt */
	QColor InterpolateColorByType( ) const;
	/** Get m_Name */	
	const QString& GetName() const;
private:
	friend class CTerrainTypeFactory;
	int			m_Id;
	QString		m_Name;
	QString		m_PicturePath;
	int			m_Oil;
	int			m_Timber;
	int			m_MovementModifier;
	int			m_DefenseModifier;
	int			m_Infrastructure;
};

