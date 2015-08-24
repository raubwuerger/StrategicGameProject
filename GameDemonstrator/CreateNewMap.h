#ifndef CREATENEWMAP_H
#define CREATENEWMAP_H

#include <QObject>
class MapView;
class CTerrainType;

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
};

#endif // CREATENEWMAP_H
