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
	bool AttacheImage(ModelUnitType* type);
	/** */
	bool ParseTerrainTypes(const QDomNode& domNode, QVector<int>& terrainTypes);
	/** */
	bool ParseAttackValues(const QDomNode& domNode, QVector<int>& attackValues);
	/** */
	bool ParseDefenseValues(const QDomNode& domNode, QVector<int>& defenseValues);
	/** */
	bool ParseAttackableUnitTypes(const QDomNode& domNode, QVector<int>& attackableUnitTypes);
	/** */
	bool ParseRecognisableUnitTypes(const QDomNode& domNode, QVector<int>& recognisableUnitTypes);
	/** */
	bool ParseTransportCapacity(const QDomNode& domNode, QVector<int>& transportCapacity);
};

#endif
