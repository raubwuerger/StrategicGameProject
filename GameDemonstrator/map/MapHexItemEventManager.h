#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapHexItem;
class HexItemInfoDialog;
class UnitTypeInfoDialog;
class MapUnitItem;
class CityTypeInfoDialog;

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
	/** */
	void SlotUpdateMapCityItemInfo(int mapCityItemId);
private:
	QVector< MapUnitItem* >			UnitItems;
	const QString DEFAULT_ENTRY;

	friend class GameDemonstrator;
	HexItemInfoDialog*	HexItemInfoDialog;
	UnitTypeInfoDialog*	UnitTypeInfoDialog;
	CityTypeInfoDialog*	CityTypeInfoDialog;
};

#endif // MAPEVENTMANAGER_H
