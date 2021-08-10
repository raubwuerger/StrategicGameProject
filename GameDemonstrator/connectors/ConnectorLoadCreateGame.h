#ifndef GameFactory_H
#define GameFactory_H

class ModelTerrainType;
class MapView;
class GameMapRepository;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
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
	void SlotCreateNewGame();
	/** */
	void SlotLoadSaveGame();
private:
	MapView				*MapViewInstance;
};

#endif



