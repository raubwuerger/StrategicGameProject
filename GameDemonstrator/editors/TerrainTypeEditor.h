#ifndef TERRAINTYPEEDITOR_H
#define TERRAINTYPEEDITOR_H

#include <QObject>
class ModelTerrainType;
class MapHexItemEventManager;
class EditorController;

class TerrainTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	TerrainTypeEditor(QObject *parent);
	/** */
	~TerrainTypeEditor();
	/** */
	void SetMapEventManager(MapHexItemEventManager* mapeventManager);
	/** */
	void SetEditorController(EditorController* editorController);
signals:
	/** */
	void SignalTerrainTypeChanged( int mapItemId, int terrainTypeId );
public slots:
	/** */
	void SlotActivateTerrainType( int terrainTypeId );
	/** */
	void SlotChangeTerrainTypeHexItem( int gameMapItemId );
	/** */
	void SlotActivated();
private:
	ModelTerrainType*		ActiveTerrainType;
	MapHexItemEventManager*	MapEventManagerInstance;
	EditorController*		EditorControllerInstance;
};

#endif // TERRAINTYPEEDITOR_H
