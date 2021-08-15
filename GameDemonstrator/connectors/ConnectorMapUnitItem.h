#ifndef CONNECTORMAPUNITITEM_H
#define CONNECTORMAPUNITITEM_H

class ConnectorMapUnitItem : public QObject
{
Q_OBJECT
public:
signals :
	/** */
	void SignalUnitItemEntered(int gameUnitId);
	/** */
	void SignalUnitItemLeft(int gameUnitId);
	/** */
	void SignalUnitItemPressedLeftButton(int gameUnitId);
	/** */
	void SignalUnitItemPressedRightButton(int gameUnitId);
	/** */
	void SignalUnitItemReleased(int gameUnitId);
};

#endif // CONNECTORMAPUNITITEM_H