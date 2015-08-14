#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapViewHexItem;
class HexItemInfoDialog;

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
public slots:
	/** */
	void UpdateMapItemInfo( int row, int col );
private:
	QVector< QVector<MapViewHexItem*> >	MapItems;

	friend class GameDemonstrator;
	HexItemInfoDialog *m_HexItemInfoDialog;
};

#endif // MAPEVENTMANAGER_H
