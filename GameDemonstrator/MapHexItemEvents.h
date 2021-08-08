#ifndef HEXITEMEVENTMANAGER_H
#define HEXITEMEVENTMANAGER_H

//================================================================================
/** Stellt SIGNALE zur Verfügung die von Benutzeraktionen ausgelöst werden. Mausbewegung auf Karte ... */
class MapHexItemEvents : public QObject
{
	Q_OBJECT
public:
signals:
	/** */
	void HexItemEntered( int row, int col );
	/** */
	void HexItemPressed( int row, int col );
private:
};

#endif // HEXITEMEVENTMANAGER_H
