#ifndef CONNECTORMAPUNITITEM_H
#define CONNECTORMAPUNITITEM_H

class ConnectorMapUnitItem : public QObject
{
Q_OBJECT
signals :
	/** */
	void SignalUnitItemEntered( int mapUnitId );
	/** */
	void SignalUnitItemLeft(int mapUnitId);
	/** */
	void SignalUnitItemPressed( int mapUnitId );
	/** */
	void SignalUnitItemReleased( int mapUnitId );
};

#endif // CONNECTORMAPUNITITEM_H