#ifndef MODELTERRAINTYPE_H
#define MODELTERRAINTYPE_H

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
	/** Get m_PictureName */
	const QString& GetPictureName() const;
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
	QString		PictureName;
	int			Infrastructure;
	int			Oil;
	int			Timber;
	int			Stone;
	int			MovementModifier;
	int			DefenseModifier;
	int			AttackModifier;
	const QImage		*Image;
};

#endif // MODELTERRAINTYPE_H

