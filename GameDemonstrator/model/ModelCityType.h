#ifndef MODELCITYTYPE_H
#define MODELCITYTYPE_H

class ModelCityType
{
public:
	/** */
	ModelCityType(int id);
	/** */
	int GetId() const;
	/** */
	const QString toString() const;
	/** */
	void SetImage(const QImage* image) { Image = image; }
	/** */
	const QImage* GetImage() const { return Image; }
	/** */
	const QString& GetPictureName() const { return PictureName; }
	/** */
	const QString& GetName() const { return Name; }
private:
	friend class ModelCityTypeFactory;
	int				Id;
	QString			Name;
	QString			PictureName;
	const QImage*	Image;
	int				Efficiency;
	int				SpezializedUnitType;
};

#endif // MODELCITYTYPE_H
