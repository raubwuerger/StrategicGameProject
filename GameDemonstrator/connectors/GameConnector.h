#ifndef GameFactory_H
#define GameFactory_H

class ModelTerrainType;
class MapView;
class ModelMapRepository;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
class GameConnector : public QObject
{
	Q_OBJECT
public:
	/** */
	GameConnector();
	/** */
	~GameConnector();
	/** */
	void Release();
	/** */
	void SetMapView( MapView* mapView );
public slots:
	/** */
	void CreateNewGame();
	/** */
	void LoadSaveGame();
private:
	MapView				*MapViewInstance;
};

#endif



