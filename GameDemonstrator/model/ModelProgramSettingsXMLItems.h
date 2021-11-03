#ifndef MODELPROGRAMSETTINGSXMLITEMS_H
#define MODELPROGRAMSETTINGSXMLITEMS_H

class ModelProgramSettingsXMLItems
{
public:
	const static QString	CONFIG_FILE_NAME;
	const static QString	ROOT_NAME;

	static const QString	NODE_LOGGING;
	static const QString	SUBNODE_GLOBALLOGLEVEL;
	static const QString	SUBNODE_SHOWLOGGINGPANE;
	static const QString	SUBNODE_LOGGINGENABLED;

	static const QString	NODE_SAVEGAME;
	static const QString	SUBNODE_SAVEGAMEPATH;

	static const QString	NODE_DEBUGMAPSETTINGS;
	static const QString	SUBNODE_ROWS;
	static const QString	SUBNODE_COLS;

	static const QString	NODE_GRAPHICSETTINGS;
	static const QString	SUBNODE_USEHIRESTERRAIN;

	static const QString	NODE_MAPHEXITEMSETTINGS;
	static const QString	SUBNODE_SHOWID;
	static const QString	SUBNODE_SHOWCOLANDROW;
	static const QString	SUBNODE_SHOWCOORDINATES;
	static const QString	SUBNODE_SHOWTEXTBORDER;
	static const QString	SUBNODE_SHOWTEXT;
	static const QString	SUBNODE_DRAWHEXBORDER;
};

#endif //MODELPROGRAMSETTINGSXMLITEMS
