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
	/** */
	void Activate(TerrainTypeEditorWidget* terrainTypeEditorWidget);
	/** */
	void Activate(UnitTypeEditorWidget* unitTypeEditorWidget);
private:
	MapView*	MapViewInstance;
};

#endif // EDITORCONTROLLER_H