#ifndef MODELUNIT_H
#define MODELUNIT_H

class ModelUnitType
{
public:
	/** */
	ModelUnitType(int id);
	/** */
	int GetId() const;
	/** */
	const QImage* GetImage() const;
	/** */
	const QString& GetName() const;
	/** */
	const QString& GetPictureName() const;
	/** */
	void SetImage(const QImage* image);
	/** */
	bool IsTerrainTypeValid(int terrainTypeId) const;
private:
	friend class ModelUnitTypeFactory;
	const int		Id;
	QString			Name;
	QString			PictureName;
	const QImage	*Image;
	int				Strength;
	int				Attack;
	int				Defense;
	int				Range;
	QVector<int>	ValidTerrainTypes;
};

#endif