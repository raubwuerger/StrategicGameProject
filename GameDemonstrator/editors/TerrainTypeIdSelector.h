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
	void Trigger();
signals:
	/** */
	void TerrainTypeActive( int terrainTypeId );
private:
	int TerrainTypeId;
};

#endif //TERRAINTYPEIDSELECTOR_H