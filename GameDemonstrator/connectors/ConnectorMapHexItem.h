#ifndef HEXITEMEVENTMANAGER_H
#define HEXITEMEVENTMANAGER_H

//================================================================================
/** Stellt SIGNALE zur Verfügung die von Benutzeraktionen ausgelöst werden. Mausbewegung auf Karte ... */
class ConnectorMapHexItem : public QObject
{
	Q_OBJECT
signals:
	/** */
	void SignalHexItemEntered(int gameMapId );
	/** */
	void SignalHexItemLeft(int gameMapId);
	/** */
	void SignalHexItemPressed(int gameMapId);
	/** */
	void SignalHexItemReleased(int gameMapId);
};

#endif // HEXITEMEVENTMANAGER_H
