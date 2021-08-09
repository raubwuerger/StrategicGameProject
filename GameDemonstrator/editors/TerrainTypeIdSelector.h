#ifndef TERRAINTYPEIDSELECTOR_H
#define TERRAINTYPEIDSELECTOR_H

class TerrainTypeIdSelector : public QObject
{
	Q_OBJECT
public:
	/** */
	TerrainTypeIdSelector( int terrainTypeId );
public slots:
	/** */
	void SlotTrigger();
signals:
	/** */
	void SignalTerrainTypeActive( int terrainTypeId );
private:
	int TerrainTypeId;
};

#endif //TERRAINTYPEIDSELECTOR_H