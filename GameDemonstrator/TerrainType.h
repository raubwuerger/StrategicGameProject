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
	const QString& GetPicturePath() const { return PicturePath; }
	/** Get m_Image */
	const QImage * GetImage() const;
	/** Set m_Image */
	void SetImage( const QImage * val);
private:
	friend class CTerrainTypeFactory;
	int			Id;
	QString		Name;
	QString		PicturePath;
	int			Oil;
	int			Timber;
	int			MovementModifier;
	int			DefenseModifier;
	int			Infrastructure;
	const QImage		*Image;
};

