#ifndef GameFactory_H
#define GameFactory_H

class ModelTerrainType;
class MapView;
class ModelMapRepository;

/** Erstellt alle Komponenten die f�r ein neues Spiel notwendig sind */
class GameFactory : public QObject
{
	Q_OBJECT
public:
	/** */
	static GameFactory* GetInstance();
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
	/** */
	GameFactory();
	/** */
	~GameFactory();
private:
	static GameFactory	*Instance;
	ModelMapRepository				*TheGameMap;
	MapView				*MapViewInstance;
};

#endif



