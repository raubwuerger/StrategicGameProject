#include "stdafx.h"
#include "EditorToolbox.h"
#include "model/ModelTerrainType.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelUnitType.h"
#include "model/ModelUnitTypeRepository.h"
#include "UnitTypeEditor.h"
#include "UnitTypeIdSelector.h"
#include "TerrainTypeEditor.h"
#include "TerrainTypeIdSelector.h"
#include "connectors/ConnectorMapHexItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "controller/EditorController.h"
#include "map/MapView.h"

EditorToolbox::EditorToolbox(QWidget *parent)
	: QToolBox(parent),
	GroupTerrainTypes(nullptr),
	GroupBuildings(nullptr),
	TerrainTypeEditorInstance(nullptr),
	MinimumEditWidth(130),
	EditorControllerInstance(nullptr)
{
}

EditorToolbox::~EditorToolbox()
{

}

void EditorToolbox::Create()
{
	EditorControllerInstance = new EditorController(MapViewInstance);
	CreateGroupTerrainTypes();
	CreateGroupUnitTypes();
	CreateGroupBuildingTypes();

	connect(this, &QToolBox::currentChanged, this, &EditorToolbox::SlotEditorTypeChanged);
	SlotEditorTypeChanged(0);
}

void EditorToolbox::SlotEditorTypeChanged(int editorIndex)
{
	if (false == EditorMap.contains(editorIndex))
	{
		return;
	}
	EditorMap[editorIndex]->SlotActivated();
}

void EditorToolbox::CreateGroupTerrainTypes()
{
	BaseEditor* editor = CreateTerrainTypeEditor();
	GroupTerrainTypes = new QButtonGroup(this);

	QGridLayout *layoutTerrainTypes = new QGridLayout;
	QMap<int, ModelTerrainType*>::const_iterator currentTerrainTypeIterator = ModelTerrainTypeRepository::GetInstance()->GetFirstIterator();

	int rowIndex = 0;
	while (currentTerrainTypeIterator != ModelTerrainTypeRepository::GetInstance()->GetLastIterator())
	{
		layoutTerrainTypes->addWidget(CreateTerrainTypeWidget(currentTerrainTypeIterator.value(), GroupTerrainTypes, new TerrainTypeIdSelector(currentTerrainTypeIterator.value()->GetId())), rowIndex++, 0);
		currentTerrainTypeIterator++;
	}

	layoutTerrainTypes->setRowStretch(10, 10); //Damit werden die vorhandenen Elemente kleiner dargestellt

	QWidget *itemTerrainType = new QWidget();
	itemTerrainType->setLayout(layoutTerrainTypes);

	int id = addItem(itemTerrainType, tr("Terrain Types"));
	EditorMap.insert(id, editor);
}

BaseEditor* EditorToolbox::CreateTerrainTypeEditor()
{
	TerrainTypeEditorInstance = new TerrainTypeEditor(nullptr);
	TerrainTypeEditorInstance->SetEditorController(EditorControllerInstance);
	TerrainTypeEditorInstance->SetMapEventManager(MapViewInstance->MapEventManagerInstance);
	EditorControllerInstance->TerrainTypeEditorInstance = TerrainTypeEditorInstance;
	return TerrainTypeEditorInstance;
}

QWidget *EditorToolbox::CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup, TerrainTypeIdSelector *connector)
{
	QIcon icon(modelTerrainType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, &QToolButton::pressed, connector, &TerrainTypeIdSelector::SlotTrigger);
	connect(connector, &TerrainTypeIdSelector::SignalTerrainTypeActive, TerrainTypeEditorInstance, &TerrainTypeEditor::SlotActivateTerrainType);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelTerrainType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

void EditorToolbox::CreateGroupUnitTypes()
{
	BaseEditor* editor = CreateUnitTypeEditor();
	GroupUnitsTypes = new QButtonGroup(this);

	QGridLayout *layoutUnitTypes = new QGridLayout;
	QMap<int, const ModelUnitType*>::const_iterator currentIterator = ModelUnitTypeRepository::GetInstance()->GetFirstIterator();

	int rowIndex = 0;
	while (currentIterator != ModelUnitTypeRepository::GetInstance()->GetLastIterator())
	{
		layoutUnitTypes->addWidget(CreateUnitTypeWidget(currentIterator.value(), GroupUnitsTypes, new UnitTypeIdSelector(currentIterator.value()->GetId())), rowIndex++, 0);
		currentIterator++;
	}

	layoutUnitTypes->setRowStretch(10, 10); //Damit werden die vorhandenen Elemente kleiner dargestellt

	QWidget *unitTypeWidget = new QWidget();
	unitTypeWidget->setLayout(layoutUnitTypes);

	int id = addItem(unitTypeWidget, tr("Unit Types"));
	EditorMap.insert(id, editor);
}

BaseEditor* EditorToolbox::CreateUnitTypeEditor()
{
	UnitTypeEditorInstance = new UnitTypeEditor(nullptr);
	UnitTypeEditorInstance->SetEditorController(EditorControllerInstance);
	UnitTypeEditorInstance->SetMapView(MapViewInstance);
	EditorControllerInstance->UnitTypeEditorInstance = UnitTypeEditorInstance;
	return UnitTypeEditorInstance;
}

QWidget* EditorToolbox::CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, UnitTypeIdSelector *connector)
{
	QIcon icon(modelUnitType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, &QToolButton::pressed, connector, &UnitTypeIdSelector::SlotTrigger);
	connect(connector, &UnitTypeIdSelector::SignalActiveUnitType, UnitTypeEditorInstance, &UnitTypeEditor::SlotActiveUnitTypeId);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelUnitType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;

}

void EditorToolbox::CreateGroupBuildingTypes()
{
	GroupBuildings = new QButtonGroup(this);
	QGridLayout *layoutBuildings = new QGridLayout;
	layoutBuildings->setRowStretch(2, 10);
	layoutBuildings->setColumnStretch(2, 10);

	QWidget *itemBuildings = new QWidget;
	itemBuildings->setLayout(layoutBuildings);

	setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));

	setMinimumWidth(MinimumEditWidth);
	addItem(itemBuildings, tr("Buildings"));
}

