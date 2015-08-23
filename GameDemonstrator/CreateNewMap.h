#ifndef CREATENEWMAP_H
#define CREATENEWMAP_H

#include <QObject>
class MapView;
class CTerrainTypeRepository;

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
	CTerrainTypeRepository	*m_TerrainTypeRepository;
};

#endif // CREATENEWMAP_H
