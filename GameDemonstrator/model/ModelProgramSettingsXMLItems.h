#ifndef MODELPROGRAMSETTINGSXMLITEMS_H
#define MODELPROGRAMSETTINGSXMLITEMS_H

class ModelProgramSettingsXMLItems
{
public:
	const static QString	CONFIG_FILE_NAME;
	const static QString	ROOT_NAME;

	static const QString	NODE_LOGGING;
	static const QString	SUBNODE_GLOBALLOGLEVEL;

	static const QString	NODE_SAVEGAME;
	static const QString	SUBNODE_SAVEGAMEPATH;

	static const QString	NODE_DEBUGMAPSETTINGS;
	static const QString	SUBNODE_ROWS;
	static const QString	SUBNODE_COLS;
};

#endif //MODELPROGRAMSETTINGSXMLITEMS
