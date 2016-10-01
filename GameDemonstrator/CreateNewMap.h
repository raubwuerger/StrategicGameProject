#ifndef CREATENEWMAP_H
#define CREATENEWMAP_H

#include <QObject>
class CMapView;
class CTerrainType;
namespace GDModel { class CGameInitialisationData; }

class CCreateNewMap : public QObject
{
	Q_OBJECT

public:
	/** */
	CCreateNewMap(QObject *parent);
	/** */
	~CCreateNewMap();
public slots:
	void DoCreateNewMap();
private:
	friend class CMapFactory;
	CMapView	*MapView;
	const CTerrainType	*DefaultTerrainType;
	GDModel::CGameInitialisationData *GameData;
};

#endif // CREATENEWMAP_H
