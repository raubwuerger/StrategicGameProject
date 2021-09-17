#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include <QGraphicsView>
class MapGraphicsScene;
class MapHexItemHexagonData;
class ConnectorMapHexItem;
class ConnectorMapUnitItem;
class ConnectorMapCityItem;
class MapHexItemEventManager;
class ModelTerrainType;
class MapHexItemHexagonData;
class MapUnitItem;
class GameMapTile;
class MapHexItem;
class KeyEventController;
class MapCityItem;

class MapView : public QGraphicsView
{
	Q_OBJECT

public:
	/** */
	MapView(QWidget *parent);
	/** */
	~MapView();
	/** */
	void Create();
	/** */
	bool AddMapHexItem(MapHexItem* mapHexItem);
	/** */
	bool AddedMapUnit(MapUnitItem *mapUnitItem);
	/** */
	bool RemoveMapUnit(MapUnitItem *mapUnitItem);
	/** */
	bool AddCity(MapCityItem *mapCityItem);
	/** */
	bool RemoveCity(MapCityItem *mapCityItem);
	/** */
	bool UpdateCity(MapCityItem *mapCityItem);
	public slots:
	/** */
	void SlotZoomIn();
	/** */
	void SlotZoomOut();
protected:
	/** */
	virtual void wheelEvent( QWheelEvent *event );
private:
	/** */
	void InitMapEventManager();
	/** */
	double CalcMapWidthInPixel() const;
	/** */
	double CalcMapHeightInPixel() const;
	/** */
	void EmitHexItemPressed();
	/** */
	void DoZoom(QWheelEvent *event);
public:
	MapGraphicsScene*		Scene;					
	static ConnectorMapHexItem*		ConnectorMapHexItemInstance;
	static ConnectorMapUnitItem*	ConnectorMapUnitItemInstance;
	static ConnectorMapCityItem*	ConnectorMapCityItemInstance;
	MapHexItemEventManager*		MapEventManagerInstance;	
private:
	KeyEventController*	KeyEventControllerInstance;
};

#endif // CMAPVIEW_H
