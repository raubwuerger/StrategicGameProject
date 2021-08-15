#ifndef EDITORCONTROLLER_H
#define EDITORCONTROLLER_H

class TerrainTypeEditor;
class UnitTypeEditor;
class MapView;
class TerrainTypeEditorWidget;
class UnitTypeEditorWidget;

class EditorController
{
public:
	/** */
	EditorController(MapView *mapView);
	/** */
	void Activate(TerrainTypeEditor* terrainTypeEditor);
	/** */
	void Activate(UnitTypeEditor* unitTypeEditor);
private:
	/** */
	void DisconnectAll();
private:
	friend class EditorToolbox;
	MapView*			MapViewInstance;
	TerrainTypeEditor*	TerrainTypeEditorInstance;
	UnitTypeEditor*		UnitTypeEditorInstance;
};

#endif // EDITORCONTROLLER_H