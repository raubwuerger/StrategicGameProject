#ifndef GameFactory_H
#define GameFactory_H

class ModelTerrainType;
class MapView;
class ModelMapRepository;

/** Erstellt alle Komponenten die f�r ein neues Spiel notwendig sind */
class ConnectorLoadCreateGame : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorLoadCreateGame();
	/** */
	~ConnectorLoadCreateGame();
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


