#ifndef MODELOWNERTYPE_H
#define MODELOWNERTYPE_H

class ModelOwnerType
{
public:
	/** */
	ModelOwnerType( int id );
	/** */
	~ModelOwnerType();
	/** */
	int GetId() const;
	/** Get Name */	
	const QString& GetName() const;
	/** */
	void SetImage(const QImage* image) { Image = image; }
	/** */
	const QImage* GetImage() const { return Image; }
	/** */
	const QString& GetPictureName() const { return PictureName; }
	/* */
	bool GetHuman() const;
	/** */
	QString toString() const;
	/** */
	const QColor& GetColor() const;
private:
	friend class ModelOwnerTypeFactory;
	const int		Id;
	bool			Human;
	QString			PictureName;
	const QImage	*Image;
	QString			Name;
	QColor			Color;
};

#endif // MODELOWNERTYPE_H
