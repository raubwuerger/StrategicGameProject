#include "stdafx.h"
#include "EditorToolbox.h"
#include "model/ModelTerrainType.h"
#include "model/ModelTerrainTypeRepository.h"
#include "TerrainTypeEditor.h"

EditorToolbox::EditorToolbox(QWidget *parent)
	: QToolBox(parent),
	GroupTerrainTypes(nullptr),
	GroupBuildings(nullptr),
	TerrainTypeEditor(nullptr)
{
}

EditorToolbox::~EditorToolbox()
{

}

void EditorToolbox::Create()
{
	GroupTerrainTypes = new QButtonGroup(this);

	connect(GroupTerrainTypes, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(ButtonGroupTerrainTypes(QAbstractButton*)));

	QGridLayout *layoutTerrainTypes = new QGridLayout;
	QMap<int,ModelTerrainType*>::const_iterator terrainTypes = ModelTerrainTypeRepository::GetInstance()->GetFirstIterator();

	//TODO: Wo werden die ganzen globalen Strings definiert!?
	QString baseTerrainPicturePath("../GameDemonstrator/Resources/");
	int rowIndex = 0;
	while( terrainTypes != ModelTerrainTypeRepository::GetInstance()->GetLastIterator() )
	{
		QString terrainPictureName(baseTerrainPicturePath);
		terrainPictureName += terrainTypes.value()->GetPicturePath();
		layoutTerrainTypes->addWidget( CreateTerrainTypeWidget( terrainTypes.value()->GetName(), GroupTerrainTypes, new ConnectorButtonTerrainTypeId( terrainTypes.value()->GetId()), terrainPictureName ), rowIndex++, 0);
		terrainTypes++;
	}

	layoutTerrainTypes->setRowStretch(10, 10); //Damit werden die vorhandenen Elemente kleiner dargestellt

	QWidget *itemTerrainType = new QWidget;
	itemTerrainType->setLayout(layoutTerrainTypes);
	addItem(itemTerrainType, tr("Terrain Types"));

	{
		GroupBuildings = new QButtonGroup(this);
		QGridLayout *layoutBuildings = new QGridLayout;
		layoutBuildings->setRowStretch(2, 10);
		layoutBuildings->setColumnStretch(2, 10);

		QWidget *itemBuildings = new QWidget;
		itemBuildings->setLayout(layoutBuildings);

		setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));

		setMinimumWidth(itemTerrainType->sizeHint().width());
		addItem(itemBuildings, tr("Buildings"));
	}
}

QWidget *EditorToolbox::CreateTerrainTypeWidget(const QString &text, QButtonGroup* buttonGroup, ConnectorButtonTerrainTypeId *connector, const QString& pictureName )
{
	QIcon icon( pictureName );

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	connect( button, SIGNAL(pressed()), connector, SLOT(Trigger()) );
	connect( connector, SIGNAL(TerrainTypeActive(int)), TerrainTypeEditor, SLOT(ActivateTerrainType(int)) );

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

void EditorToolbox::ButtonGroupTerrainTypes( QAbstractButton *button )
{
	// 	QList<QAbstractButton *> buttons = m_ButtonGroupTerrainTypes->buttons();
	// 	foreach (QAbstractButton *myButton, buttons) 
	// 	{
	// 		if (myButton != button)
	// 		{
	// 			button->setChecked(false);
	// 		}
	// 		else
	// 		{
	// 			button->setChecked(true);
	// 		}
	// 	}
	//TODO: Do something ...
	// 	QString text = button->text();
	// 	if (text == tr("Blue Grid"))
	// 		scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
	// 	else if (text == tr("White Grid"))
	// 		scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
	// 	else if (text == tr("Gray Grid"))
	// 		scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
	// 	else
	// 		scene->setBackgroundBrush(QPixmap(":/images/background4.png"));
	// 
	// 	scene->update();
	// 	view->update();
}

/************************************************************************/
/* CConnectorButtonTerrainTypeId                                        */
/************************************************************************/
ConnectorButtonTerrainTypeId::ConnectorButtonTerrainTypeId( int terrainTypeId ) 
	: TerrainTypeId(terrainTypeId)
{

}

void ConnectorButtonTerrainTypeId::Trigger()
{
	emit TerrainTypeActive(TerrainTypeId);
}
