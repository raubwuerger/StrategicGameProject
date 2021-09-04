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
#include "CityTypeEditor.h"

EditorToolbox::EditorToolbox(QWidget *parent)
	: QToolBox(parent),
	GroupTerrainTypes(nullptr),
	GroupBuildings(nullptr),
	GroupOwnerTypes(nullptr),
	TerrainTypeEditorInstance(nullptr),
	UnitTypeEditorInstance(nullptr),
	OwnerTypeEditorInstance(nullptr),
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
	CreateGroupCityType();
	CreateGroupUnitTypes();
	CreateGroupOwnerType();
	CreateGroupBuildingTypes();

	connect(this, &QToolBox::currentChanged, this, &EditorToolbox::SlotEditorTypeChanged);
	SlotEditorTypeChanged(0); //TerrainTypeEditor
}

void EditorToolbox::SlotEditorTypeChanged(int editorIndex)
{
	if (false == EditorMap.contains(editorIndex))
	{
		return;
	}

	QMapIterator<int, BaseEditor*> current(EditorMap);
	while (current.hasNext())
	{
		current.next().value()->SlotDeactivated();
		current.next().value()->SetActive(false);
	}

	EditorMap[editorIndex]->SlotActivated();
	EditorMap[editorIndex]->SetActive(true);
}

void EditorToolbox::CreateGroupTerrainTypes()
{
	const int COLUMN_INDEX = 0;
	BaseEditor* editor = CreateTerrainTypeEditor();
	GroupTerrainTypes = new QButtonGroup(this);

	QGridLayout *layoutTerrainTypes = new QGridLayout;
	int rowIndex = 0;
	layoutTerrainTypes->addWidget(CreateReleaseTerrainTypeWidget(GroupTerrainTypes, new TerrainTypeIdSelector(rowIndex++)));

	QMap<int, ModelTerrainType*>::const_iterator currentTerrainTypeIterator = ModelTerrainTypeRepository::GetInstance()->GetFirstIterator();
	while (currentTerrainTypeIterator != ModelTerrainTypeRepository::GetInstance()->GetLastIterator())
	{
		layoutTerrainTypes->addWidget(CreateTerrainTypeWidget(currentTerrainTypeIterator.value(), GroupTerrainTypes), rowIndex++, COLUMN_INDEX);
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

QWidget * EditorToolbox::CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup)
{
	QIcon icon(modelTerrainType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	TerrainTypeIdSelector *connector = new TerrainTypeIdSelector(modelTerrainType->GetId());
	connect(button, &QToolButton::pressed, connector, &TerrainTypeIdSelector::SlotTrigger);
	connect(connector, &TerrainTypeIdSelector::SignalTerrainTypeActive, TerrainTypeEditorInstance, &TerrainTypeEditor::SlotActivateTerrainType);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelTerrainType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

QWidget * EditorToolbox::CreateReleaseTerrainTypeWidget(QButtonGroup* buttonGroup, TerrainTypeIdSelector *connector)
{
	QIcon icon(".\\Resources\\sign_forbidden.ico");

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, &QToolButton::pressed, connector, &TerrainTypeIdSelector::SlotTrigger);
	connect(connector, &TerrainTypeIdSelector::SignalTerrainTypeActive, TerrainTypeEditorInstance, &TerrainTypeEditor::SlotActivateTerrainType);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel("No Type"), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

void EditorToolbox::CreateGroupUnitTypes()
{
	const int COLUMN_INDEX = 0;
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

#include "model/ModelOwnerTypeRepository.h"
#include "model/ModelOwnerType.h"
#include "OwnerTypeIdSelector.h"
void EditorToolbox::CreateGroupOwnerType()
{
	const int COLUMN_INDEX = 0;
	BaseEditor* editor = CreateOwnerTypeEditor();
	GroupOwnerTypes = new QButtonGroup(this);

	QGridLayout *layout = new QGridLayout;
	QMap<int, const ModelOwnerType*>::const_iterator currentIterator = ModelOwnerTypeRepository::GetInstance()->GetFirstIterator();

	int rowIndex = 0;
	while (currentIterator != ModelOwnerTypeRepository::GetInstance()->GetLastIterator())
	{
		layout->addWidget(CreateOwnerTypeWidget(currentIterator.value(), GroupOwnerTypes, new OwnerTypeIdSelector(currentIterator.value()->GetId())), rowIndex++, 0);
		currentIterator++;
	}

	layout->setRowStretch(10, 10); //Damit werden die vorhandenen Elemente kleiner dargestellt

	QWidget *widget = new QWidget();
	widget->setLayout(layout);

	int id = addItem(widget, tr("Owner types"));
	EditorMap.insert(id, editor);
}

#include "OwnerTypeIdSelector.h"
#include "model/ModelOwnerType.h"
#include "OwnerTypeEditor.h"
QWidget * EditorToolbox::CreateOwnerTypeWidget(const ModelOwnerType* modelOwnerType, QButtonGroup* buttonGroup, OwnerTypeIdSelector *selector)
{
	QIcon icon(modelOwnerType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, &QToolButton::pressed, selector, &OwnerTypeIdSelector::SlotTrigger);
	connect(selector, &OwnerTypeIdSelector::SignalOwnerTypeActive, OwnerTypeEditorInstance, &OwnerTypeEditor::SlotActiveOwnerTypeId);
	connect(selector, &OwnerTypeIdSelector::SignalOwnerTypeActive, UnitTypeEditorInstance, &UnitTypeEditor::SlotActiveOwnerTypeId);
	connect(selector, &OwnerTypeIdSelector::SignalOwnerTypeActive, CityTypeEditorInstance, &CityTypeEditor::SlotActiveOwnerTypeId);

	//TODO: Gehört das hier her?
	const int OWNER_TYPE_NEUTRAL = 1;
	emit selector->SignalOwnerTypeActive(OWNER_TYPE_NEUTRAL);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelOwnerType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

#include "OwnerTypeEditor.h"
BaseEditor* EditorToolbox::CreateOwnerTypeEditor()
{
	OwnerTypeEditorInstance = new OwnerTypeEditor(nullptr);
	OwnerTypeEditorInstance->SetEditorController(EditorControllerInstance);
	EditorControllerInstance->OwnerTypeEditorInstance = OwnerTypeEditorInstance;
	return OwnerTypeEditorInstance;
}

#include "Model/ModelCityTypeRepository.h"
#include "Model/ModelCityType.h"
#include "CityTypeIdSelector.h"
void EditorToolbox::CreateGroupCityType()
{
	BaseEditor* editor = CreateCityTypeEditor();
	GroupCityTypes = new QButtonGroup(this);

	QGridLayout *layout = new QGridLayout;
	QMap<int, const ModelCityType*>::const_iterator currentIterator = ModelCityTypeRepository::GetInstance()->GetFirstIterator();

	int rowIndex = 0;
	while (currentIterator != ModelCityTypeRepository::GetInstance()->GetLastIterator())
	{
		layout->addWidget(CreateCityTypeWidget(currentIterator.value(), GroupCityTypes, new CityTypeIdSelector(currentIterator.value()->GetId())), rowIndex++, 0);
		currentIterator++;
	}

	layout->setRowStretch(10, 10); //Damit werden die vorhandenen Elemente kleiner dargestellt

	QWidget *widget = new QWidget();
	widget->setLayout(layout);

	int id = addItem(widget, tr("City types"));
	EditorMap.insert(id, editor);

}

QWidget * EditorToolbox::CreateCityTypeWidget(const ModelCityType* modelCityType, QButtonGroup* buttonGroup, CityTypeIdSelector *selector)
{
	QIcon icon(modelCityType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, &QToolButton::pressed, selector, &CityTypeIdSelector::SlotTrigger);
	connect(selector, &CityTypeIdSelector::SignalCityTypeActive, CityTypeEditorInstance, &CityTypeEditor::SlotActiveCityTypeId);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelCityType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

BaseEditor* EditorToolbox::CreateCityTypeEditor()
{
	CityTypeEditorInstance = new CityTypeEditor(nullptr);
	CityTypeEditorInstance->MapViewInstance = MapViewInstance;
	CityTypeEditorInstance->EditorControllerInstance = EditorControllerInstance;
	EditorControllerInstance->CityTypeEditorInstance = CityTypeEditorInstance;
	return CityTypeEditorInstance;
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

