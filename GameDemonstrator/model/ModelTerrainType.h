#pragma once

class ModelTerrainType
{
public:
	/** */
	ModelTerrainType( int id );
	/** */
	~ModelTerrainType();
	/** Get m_Id */	
	int GetId() const;
	/** Wird sp�ter entfernt */
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
	friend class ModelTerrainTypeFactory;
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

