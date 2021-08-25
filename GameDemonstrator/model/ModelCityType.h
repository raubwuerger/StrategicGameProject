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
	const QImage* GetImage() const { return Image; }
	/** */
	const QString& GetPictureName() const { return PictureName; }
	/** */
	void SetName(const QString& name) { Name = name; }
	/** */
	const QString& GetName() const { return Name; }
	/** */
	bool IsPlaceableOnTerrainType(int terrainTypeId) const;
	/** */
	int GetDefenceValue() const { return DefenceValue; }
private:
	friend class ModelCityTypeFactory;
	int				Id;
	QString			Name;
	QString			PictureName;
	const QImage*	Image;
	int				Efficiency;
	int				SpezializedUnitType;
	QVector<int>	PlacableTerrainTypes;
	int				DefenceValue;
};

#endif // MODELCITYTYPE_H
