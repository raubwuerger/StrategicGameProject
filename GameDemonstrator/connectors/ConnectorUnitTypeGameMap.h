#ifndef CONNECTORUNITTYPEGAMEMAP_H
#define CONNECTORUNITTYPEGAMEMAP_H

class ConnectorUnitTypeGameMap : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorUnitTypeGameMap();
	/** */
	~ConnectorUnitTypeGameMap();
public slots:
	/** */
	void UnitTypeAdded(int modelMapId, int unitTypeId);
};

#endif // CONNECTORUNITTYPEGAMEMAP_H
