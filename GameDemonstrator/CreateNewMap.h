#ifndef CREATENEWMAP_H
#define CREATENEWMAP_H

#include <QObject>
class MapView;
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
	MapView	*m_MapView;
	const CTerrainType	*m_DefaultTerrainType;
	GDModel::CGameInitialisationData *m_GameData;
};

#endif // CREATENEWMAP_H
