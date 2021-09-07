#ifndef CONNECTORMAPCITYITEM_H
#define CONNECTORMAPCITYITEM_H

class ConnectorMapCityItem : public QObject
{
	Q_OBJECT
public:
signals :
	/** */
	void SignalCityItemEntered(int gameCityId);
	/** */
	void SignalHexItemEntered(int gameMapItemId);
	/** */
	void SignalCityItemPressedLeftButton(int gameCityId);
	/** */
	void SignalCityItemPressedRightButton(int gameCityId);
	/** */
	void SignalCityItemDoubleClick(int gameCityId);
};

#endif // CONNECTORMAPCITYITEM_H