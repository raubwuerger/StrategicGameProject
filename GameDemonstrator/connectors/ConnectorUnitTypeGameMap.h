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
	void SlotUnitTypeAdded(int modelMapId, int unitTypeId);
};

#endif // CONNECTORUNITTYPEGAMEMAP_H
