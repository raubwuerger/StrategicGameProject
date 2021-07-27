#ifndef CREATENEWMAP_H
#define CREATENEWMAP_H

#include <QObject>
class MapView;
class TerrainType;
class GameInitialisationData;

class CreateNewMap : public QObject
{
	Q_OBJECT
public:
	/** */
	CreateNewMap(QObject *parent);
	/** */
	~CreateNewMap();
public slots:
	void DoCreateNewMap();
private:
	friend class MapFactory;
	MapView	*MapView;
	const TerrainType	*DefaultTerrainType;
	GameInitialisationData *GameData;
};

#endif // CREATENEWMAP_H
