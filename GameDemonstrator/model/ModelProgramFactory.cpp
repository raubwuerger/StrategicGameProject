#include "stdafx.h"
#include "ModelProgramFactory.h"
#include "ModelProgramSettingsXMLItems.h"
#include "ModelProgramSettings.h"
#include "LogInterface.h"
#include <QDomNode>
#include "DomValueExtractor.h"
#include "io/ConfigFileLoader.h"

ModelProgramSettings* ModelProgramFactory::ModelProgramSettingsInstance = nullptr;

ModelProgramFactory::ModelProgramFactory()
{
	if (nullptr == ModelProgramSettingsInstance)
	{
		ModelProgramSettingsInstance = new ModelProgramSettings();
	}
}

ModelProgramFactory::~ModelProgramFactory()
{
}

bool ModelProgramFactory::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelProgramSettingsXMLItems::CONFIG_FILE_NAME, ModelProgramSettingsXMLItems::ROOT_NAME))
	{
		return false;
	}

	QDomNodeList programSettingsNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < programSettingsNodes.count(); i++)
	{
		QString currentNodeName = programSettingsNodes.at(i).nodeName();
		if (currentNodeName == ModelProgramSettingsXMLItems::NODE_LOGGING)
		{
			DomValueExtractor extractor(programSettingsNodes.at(i));
			if (false == extractor.ExtractValue(ModelProgramSettingsXMLItems::SUBNODE_GLOBALLOGLEVEL, ModelProgramSettings::GlobalLogLevel))
			{
				jha::GetLog()->Log_WARNING(QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettingsXMLItems::CONFIG_FILE_NAME).arg(ModelProgramSettingsXMLItems::SUBNODE_GLOBALLOGLEVEL));
				return false;
			}
			continue;
		}

		if (currentNodeName == ModelProgramSettingsXMLItems::NODE_DEBUGMAPSETTINGS)
		{
			DomValueExtractor extractorRows(programSettingsNodes.at(i));
			if (false == extractorRows.ExtractValue(ModelProgramSettingsXMLItems::SUBNODE_ROWS, ModelProgramSettings::DebugRows))
			{
				jha::GetLog()->Log_WARNING(QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettingsXMLItems::CONFIG_FILE_NAME).arg(ModelProgramSettingsXMLItems::SUBNODE_ROWS));
				return false;
			}
			DomValueExtractor extractorCols(programSettingsNodes.at(i));
			if (false == extractorCols.ExtractValue(ModelProgramSettingsXMLItems::SUBNODE_COLS, ModelProgramSettings::DebugCols))
			{
				jha::GetLog()->Log_WARNING(QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettingsXMLItems::CONFIG_FILE_NAME).arg(ModelProgramSettingsXMLItems::SUBNODE_COLS));
				return false;
			}
			continue;
		}

		if (currentNodeName == ModelProgramSettingsXMLItems::NODE_SAVEGAME)
		{
			DomValueExtractor extractor(programSettingsNodes.at(i));
			if (false == extractor.ExtractValue(ModelProgramSettingsXMLItems::SUBNODE_SAVEGAMEPATH, ModelProgramSettings::SaveGamePath))
			{
				jha::GetLog()->Log_WARNING(QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettingsXMLItems::CONFIG_FILE_NAME).arg(ModelProgramSettingsXMLItems::SUBNODE_SAVEGAMEPATH));
				return false;
			}
			continue;
		}
		
		jha::GetLog()->Log_DEBUG(QObject::tr("Unknown node found! %1").arg(currentNodeName));
	}

	QString globalLogLevel = ModelProgramSettings::GlobalLogLevel;
	QString savegamePath = ModelProgramSettings::SaveGamePath;
	int debugRows = ModelProgramSettings::DebugRows;
	int debugCols = ModelProgramSettings::DebugCols;

	return true;
}

ModelProgramSettings* ModelProgramFactory::GetConfig()
{
	return ModelProgramSettingsInstance;
}
