#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapHexItem;
class HexItemInfoDialog;
class MapUnitItem;

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
	void RegisterMapItem( MapHexItem* mapItem );
	/** */
	const MapHexItem* FindItemByIndex( int row, int col ) const;
	/** */
	MapHexItem* FindItemByIndexNonConst( int row, int col );
	/** */
	void RegisterUnitItem(MapUnitItem* unitItem);
public slots:
	/** */
	void UpdateMapItemInfo( int row, int col );
private:
	QVector< QVector<MapHexItem*> >	MapItems;
	QVector< MapUnitItem* >			UnitItems;

	friend class GameDemonstrator;
	HexItemInfoDialog *HexItemInfoDialog;
};

#endif // MAPEVENTMANAGER_H
