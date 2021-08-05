#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapViewHexItem;
class HexItemInfoDialog;
class MapViewUnitItem;

class MapEventManager : public QObject
{
	Q_OBJECT
public:
	/** */
	MapEventManager(QObject *parent);
	/** */
	~MapEventManager();
	/** */
	void InitMapItemsRegistry( int rows, int cols );
	/** */
	void RegisterMapItem( MapViewHexItem* mapItem );
	/** */
	const MapViewHexItem* FindItemByIndex( int row, int col ) const;
	/** */
	MapViewHexItem* FindItemByIndexNonConst( int row, int col );
	/** */
	void RegisterUnitItem(MapViewUnitItem* unitItem);
public slots:
	/** */
	void UpdateMapItemInfo( int row, int col );
private:
	QVector< QVector<MapViewHexItem*> >	MapItems;
	QVector< MapViewUnitItem* >			UnitItems;

	friend class GameDemonstrator;
	HexItemInfoDialog *HexItemInfoDialog;
};

#endif // MAPEVENTMANAGER_H
