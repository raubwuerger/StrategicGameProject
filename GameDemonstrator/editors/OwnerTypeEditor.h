#ifndef OWNERTYPEEDITOR_H
#define OWNERTYPEEDITOR_H

class ModelOwnerType;
class EditorController;
#include "BaseEditor.h"

class OwnerTypeEditor : public BaseEditor
{
public:
	/** */
	OwnerTypeEditor(QObject *parent);
	/** */
	void SetEditorController(EditorController* editorController);
public slots:
	/** */
	void SlotActivated() override;
	/** */
	void SlotActiveOwnerTypeId(int ownerTypeId);
private:
	const ModelOwnerType*	ActiveModelOwnerType;
	EditorController*		EditorControllerInstance;
};

#endif // OWNERTYPEEDITOR_H