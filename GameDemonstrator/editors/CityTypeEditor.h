#ifndef CITYTYPEEDITOR_H
#define CITYTYPEEDITOR_H

class ModelCityType;
class EditorController;
#include "BaseEditor.h"

class CityTypeEditor : public BaseEditor
{
public:
	/** */
	CityTypeEditor(QObject *parent);
	/** */
	void SetEditorController(EditorController* editorController);
public slots:
	/** */
	void SlotActivated() override;
	/** */
	void SlotDeactivated() override;
	/** */
	void SlotActiveCityTypeId(int CityTypeId);
	/** */
	void SlotAddCity(int mapItemId);
private:
	const ModelCityType*	ActiveModelCityType;
	EditorController*		EditorControllerInstance;
};

#endif // CITYTYPEEDITOR_H