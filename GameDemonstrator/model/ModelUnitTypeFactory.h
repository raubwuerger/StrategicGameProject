#ifndef MODELUNITFACTORY_H
#define MODELUNITFACTORY_H

class ModelUnitType;
class QDomNode;

class ModelUnitTypeFactory
{
public:
	/** */
	ModelUnitTypeFactory();
	/** */
	~ModelUnitTypeFactory();
	/** */
	bool Create();
private:
	/** */
	ModelUnitType* CreateFromXML(const QDomNode& node);
	/** */
	const QImage* LoadImage(const QString& path);
	/** */
	bool AttacheImage(ModelUnitType* modelUnit);
	/** */
	bool ExtractTerrainTypes(const QDomNode& domNode, QVector<int>& terrainTypes);
	/** */
	bool ExtractAttackValues(const QDomNode& domNode, QVector<int>& attackValues);
	/** */
	bool ExtractDefenseValues(const QDomNode& domNode, QVector<int>& defenseValues);
};

#endif
