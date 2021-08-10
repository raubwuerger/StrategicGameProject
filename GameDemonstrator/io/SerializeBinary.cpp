#include "stdafx.h"
#include "SerializeBinary.h"
#include "game\GameMapRepository.h"


SerializeBinary::SerializeBinary()
{
}


SerializeBinary::~SerializeBinary()
{
}

bool SerializeBinary::SaveGame( const QString& saveGameName )
{
	//TODO: Not yet implemented!!!
	return false;
/*	QFile file("MapFile.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);

	for( int row = 0; row < gameMap.GetMapItems().size(); row++ )
	{
		for( int col = 0;  col < gameMap.GetMapItems().at(row).size(); col++ )
		{
			out << gameMap.GetMapItems().at(row).begin();
		}
	}
*/
}

bool SerializeBinary::LoadGame( const QString& saveGameName )
{
	//TODO: Not yet implemented!!!
	return false;
}
