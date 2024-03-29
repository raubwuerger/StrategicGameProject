#ifndef EDITORCONTROLLER_H
#define EDITORCONTROLLER_H

class TerrainTypeEditor;
class UnitTypeEditor;
class MapView;
class TerrainTypeEditorWidget;
class UnitTypeEditorWidget;
class OwnerTypeEditor;
class CityTypeEditor;

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
	void Activate(OwnerTypeEditor* ownerTypeEditor);
	/** */
	void Activate(CityTypeEditor* cityTypeEditor);
private:
	/** */
	void DisconnectAll();
private:
	friend class EditorToolbox;
	MapView*			MapViewInstance;
	TerrainTypeEditor*	TerrainTypeEditorInstance;
	UnitTypeEditor*		UnitTypeEditorInstance;
	OwnerTypeEditor*	OwnerTypeEditorInstance;
	CityTypeEditor*		CityTypeEditorInstance;
};

#endif // EDITORCONTROLLER_H