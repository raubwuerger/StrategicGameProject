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
	/** Get m_PicturePath */
	const QString& GetPicturePath() const { return m_PicturePath; }
	/** Get m_Image */
	const QImage * GetImage() const;
	/** Set m_Image */
	void SetImage( const QImage * val);
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
	const QImage		*m_Image;
};

