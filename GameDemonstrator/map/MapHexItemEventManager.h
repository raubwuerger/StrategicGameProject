#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapHexItem;
class HexItemInfoDialog;
class UnitTypeInfoDialog;
class MapUnitItem;

class MapHexItemEventManager : public QObject
{
	Q_OBJECT
public:
	/** */
	MapHexItemEventManager(QObject *parent);
	/** */
	~MapHexItemEventManager();
	/** */
	MapHexItem* FindMapHexItemByIndexNonConst( int row, int col );
public slots:
	/** */
	void SlotUpdateMapItemInfo( int row, int col );
	/** */
	void SlotUpdateMapUnitItemInfo(int mapUnitItemId);
private:
	QVector< MapUnitItem* >			UnitItems;
	const QString DEFAULT_ENTRY;

	friend class GameDemonstrator;
	HexItemInfoDialog*	HexItemInfoDialog;
	UnitTypeInfoDialog*	UnitTypeInfoDialog;
};

#endif // MAPEVENTMANAGER_H
