#include "stdafx.h"
#include "SaveBinary.h"
#include "Model\GameMap.h"


CSaveBinary::CSaveBinary()
{
}


CSaveBinary::~CSaveBinary()
{
}

bool CSaveBinary::DoSerializeGame( const GDModel::GameMap& gameMap )
{
	QFile file("MapFile.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);

	for( int row = 0; row < gameMap.GetMapItems().size(); row++ )
	{
		for( int col = 0;  col < gameMap.GetMapItems().at(row).size(); col++ )
		{
			out << gameMap.GetMapItems().at(row).begin();
		}
	}

	return false;
}

bool CSaveBinary::DoDeserializeGame( GDModel::GameMap& gameMap )
{
	return false;
}
