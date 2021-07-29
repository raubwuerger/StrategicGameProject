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
	/** */
	QString toString() const;
private:
	friend class ModelTerrainTypeFactory;
	int			Id;
	QString		Name;
	QString		PicturePath;
	int			Infrastructure;
	int			Oil;
	int			Timber;
	int			Stone;
	int			MovementModifier;
	int			DefenseModifier;
	int			AttackModifier;
	const QImage		*Image;
};

