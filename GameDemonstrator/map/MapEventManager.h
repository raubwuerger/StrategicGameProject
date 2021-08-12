#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapHexItem;
class HexItemInfoDialog;
class UnitTypeInfoDialog;
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
	void InitGameMapRegistry();
	/** */
	void RegisterMapHexItem( MapHexItem* mapItem );
	/** */
	const MapHexItem* FindMapHexItemByIndex( int row, int col ) const;
	/** */
	MapHexItem* FindIMapHextemByIndexNonConst( int row, int col );
	/** */
	void RegisterMapUnitItem(MapUnitItem* unitItem);
public slots:
	/** */
	void SlotUpdateMapItemInfo( int row, int col );
	/** */
	void SlotUpdateMapUnitItemInfo(int mapUnitItemId);
private:
	QVector< QVector<MapHexItem*> >	MapItems;
	QVector< MapUnitItem* >			UnitItems;
	const QString DEFAULT_ENTRY;

	friend class GameDemonstrator;
	HexItemInfoDialog*	HexItemInfoDialog;
	UnitTypeInfoDialog*	UnitTypeInfoDialog;
};

#endif // MAPEVENTMANAGER_H
