#pragma once

class ModelTerrainType;
class MapView;
class ModelMapRepository;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
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
		void CreateNewGame();
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



