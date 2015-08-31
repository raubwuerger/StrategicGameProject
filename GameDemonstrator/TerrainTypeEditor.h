#ifndef TERRAINTYPEEDITOR_H
#define TERRAINTYPEEDITOR_H

#include <QObject>

class CTerrainTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	CTerrainTypeEditor(QObject *parent);
	/** */
	~CTerrainTypeEditor();
public slots:
	/** */
	void ActivateTerrainType( int terrainTypeId );
	/** */
	void ChangeTerrainTypeHexItem( int row, int col );
private:

};

#endif // TERRAINTYPEEDITOR_H
