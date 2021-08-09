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
#include "connectors/ConnectorTerrainEditorGameMap.h"
#include "connectors/ConnectorUnitTypeGameMap.h"

EditorToolbox::EditorToolbox(QWidget *parent)
	: QToolBox(parent),
	GroupTerrainTypes(nullptr),
	GroupBuildings(nullptr),
	TerrainTypeEditorInstance(nullptr),
	MinimumEditWidth(130)
{
}

EditorToolbox::~EditorToolbox()
{

}

void EditorToolbox::Create()
{
	CreateGroupTerrainTypes();
	CreateGroupUnitTypes();
	CreateGroupBuildingTypes();
	//TODO: connect überarbeiten... Wenn UnitEditor ausgewählt ist sollte dieser Verbunden werden!
	connect(ConnectorMapHexItemInstance, &ConnectorMapHexItem::HexItemPressed, TerrainTypeEditorInstance, &TerrainTypeEditor::ChangeTerrainTypeHexItem);

}

void EditorToolbox::CreateGroupTerrainTypes()
{
	CreateTerrainTypeEditor(MapEventManagerInstance);
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

	QWidget *itemTerrainType = new QWidget;
	itemTerrainType->setLayout(layoutTerrainTypes);
	int width = itemTerrainType->sizeHint().width();

	addItem(itemTerrainType, tr("Terrain Types"));
}

QWidget *EditorToolbox::CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup, TerrainTypeIdSelector *connector)
{
	QIcon icon(modelTerrainType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, SIGNAL(pressed()), connector, SLOT(Trigger()));
	connect(connector, SIGNAL(TerrainTypeActive(int)), TerrainTypeEditorInstance, SLOT(ActivateTerrainType(int)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelTerrainType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

void EditorToolbox::CreateTerrainTypeEditor(MapEventManager* mapEventManager)
{
	ConnectorEditorModelRepositoryInstance = new ConnectorTerrainEditorGameMap();
	TerrainTypeEditorInstance = new TerrainTypeEditor(nullptr);
	TerrainTypeEditorInstance->SetMapEventManager(MapEventManagerInstance);
	QObject::connect(TerrainTypeEditorInstance, &TerrainTypeEditor::TerrainTypeChanged,
		ConnectorEditorModelRepositoryInstance, &ConnectorTerrainEditorGameMap::TerrainTypeChanged);
}

void EditorToolbox::CreateGroupUnitTypes()
{
	CreateUnitTypeEditor(MapEventManagerInstance);
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

	QWidget *itemUnitType = new QWidget;
	itemUnitType->setLayout(layoutUnitTypes);
	int width = itemUnitType->sizeHint().width();

	addItem(itemUnitType, tr("Unit Types"));
}

QWidget* EditorToolbox::CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, UnitTypeIdSelector *connector)
{
	QIcon icon(modelUnitType->GetPictureName());

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect(button, SIGNAL(pressed()), connector, SLOT(Trigger()));
	connect(connector, SIGNAL(UnitTypeActive(int)), UnitTypeEditorInstance, SLOT(UnitAdded(int)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(modelUnitType->GetName()), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;

}

void EditorToolbox::CreateUnitTypeEditor(MapEventManager* mapEventManager)
{
	ConnectorUnitTypeEditorGameMapInstance = new ConnectorUnitTypeGameMap();

	UnitTypeEditorInstance = new UnitTypeEditor(nullptr);
	UnitTypeEditorInstance->SetMapEventManager(MapEventManagerInstance);
	QObject::connect(UnitTypeEditorInstance, &UnitTypeEditor::UnitAdded,
		ConnectorUnitTypeEditorGameMapInstance, &ConnectorUnitTypeGameMap::UnitTypeAdded);
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

