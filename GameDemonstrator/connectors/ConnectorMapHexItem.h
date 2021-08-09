#ifndef HEXITEMEVENTMANAGER_H
#define HEXITEMEVENTMANAGER_H

//================================================================================
/** Stellt SIGNALE zur Verf�gung die von Benutzeraktionen ausgel�st werden. Mausbewegung auf Karte ... */
class ConnectorMapHexItem : public QObject
{
	Q_OBJECT
public:
signals:
	/** */
	void SignalHexItemEntered( int row, int col );
	/** */
	void SignalHexItemPressed(int row, int col);
private:
};

#endif // HEXITEMEVENTMANAGER_H
