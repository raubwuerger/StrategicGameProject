#ifndef CONNECTORMAPCITYITEM_H
#define CONNECTORMAPCITYITEM_H

class ConnectorMapCityItem : public QObject
{
	Q_OBJECT
public:
signals :
	/** */
	void SignalCityItemEntered(int gameCityId);

};

#endif // CONNECTORMAPCITYITEM_H