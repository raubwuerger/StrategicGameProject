#ifndef TERRAINTYPEEDITORWIDGET_H
#define TERRAINTYPEEDITORWIDGET_H

class EditorController;

class TerrainTypeEditorWidget : public QWidget
{
public:
	/** */
	TerrainTypeEditorWidget(EditorController* editorController);
public slots:
	/** */
	void SlotActivated();
private:
	EditorController*	EditorControllerInstance;
};

#endif // TERRAINTYPEEDITORWIDGET_H