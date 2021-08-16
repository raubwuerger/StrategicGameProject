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
	MapHexItem* FindMapHexItem(int gameMapItemId) const;
public slots:
	/** */
	void SlotUpdateMapItemInfo(int gameMapItemId);
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
