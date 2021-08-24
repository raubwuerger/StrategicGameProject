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
	/** */
	bool IsPlaceableOnTerrainType(int terrainTypeId) const;
private:
	friend class ModelCityTypeFactory;
	int				Id;
	QString			Name;
	QString			PictureName;
	const QImage*	Image;
	int				Efficiency;
	int				SpezializedUnitType;
	QVector<int>	PlacableTerrainTypes;
};

#endif // MODELCITYTYPE_H
