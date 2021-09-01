#include "stdafx.h"
#include "ConnectorSaveGame.h"
#include "io\SerializeXML.h"
#include "GameDemonstrator.h"

ConnectorSaveGame::ConnectorSaveGame()
	: GameDemonstratorObject(nullptr)
{

}

void ConnectorSaveGame::SlotSaveGame()
{
	QFileDialog dialog;

	QString caption("Save file");
	QString proposedName(".\\savegames\\FileToSave.xml");
	QString filter("Savegame files (*.xml )");
	QString saveFileName = dialog.getSaveFileName(GameDemonstratorObject, caption, proposedName, filter);
	if (true == saveFileName.isEmpty())
	{
		return;
	}

	SerializeXML serializer;
	if (false == serializer.SaveGame(saveFileName))
	{
		return; //TODO: Error message
	}
}
