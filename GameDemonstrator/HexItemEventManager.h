#ifndef HEXITEMEVENTMANAGER_H
#define HEXITEMEVENTMANAGER_H

//================================================================================
/** Stellt SIGNALE zur Verf�gung die von Benutzeraktionen ausgel�st werden. Mausbewegung auf Karte ... */
class HexItemEventManager : public QObject
{
	Q_OBJECT
public:
	/** */
	HexItemEventManager();
signals:
	/** */
	void HexItemEntered( int row, int col );
	/** */
	void HexItemPressed( int row, int col );
private:
};

#endif // HEXITEMEVENTMANAGER_H