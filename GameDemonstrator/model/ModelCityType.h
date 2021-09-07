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
	/** */
	int GetEfficiency() const { return Efficiency; }
	/** */
	int GetSpezializedUnitType() const { return SpezializedUnitType; }
	/** */
	int GetBaseProductionPoints() const { return BaseProductionPoints; }
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
	int				BaseProductionPoints;
};

#endif // MODELCITYTYPE_H
