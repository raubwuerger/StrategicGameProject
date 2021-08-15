#ifndef UNITTYPEEDITORWIDGET_H
#define UNITTYPEEDITORWIDGET_H

class EditorController;

class UnitTypeEditorWidget : public QWidget
{
public:
	/** */
	UnitTypeEditorWidget(EditorController* editorController);
public slots:
	/** */
	void SlotActivated();
private:
	EditorController*	EditorControllerInstance;
};

#endif // UNITTYPEEDITORWIDGET_H