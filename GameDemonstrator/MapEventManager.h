#ifndef MAPEVENTMANAGER_H
#define MAPEVENTMANAGER_H

#include <QObject>
class MapViewHexItem;
class CHexItemInfoDialog;

class CMapEventManager : public QObject
{
	Q_OBJECT
public:
	/** */
	CMapEventManager(QObject *parent);
	/** */
	~CMapEventManager();
	/** */
	void InitMapItemsRegistry( int rows, int cols );
	/** */
	void RegisterMapItem( MapViewHexItem* mapItem );
	/** */
	const MapViewHexItem* FindItemByIndex( int row, int col ) const;
	/** */
	MapViewHexItem* FindItemByIndexNonConst( int row, int col );
public slots:
	/** */
	void UpdateMapItemInfo( int row, int col );
private:
	QVector< QVector<MapViewHexItem*> >	MapItems;

	friend class GameDemonstrator;
	CHexItemInfoDialog *HexItemInfoDialog;
};

#endif // MAPEVENTMANAGER_H
