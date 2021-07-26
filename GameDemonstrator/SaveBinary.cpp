#include "stdafx.h"
#include "SaveBinary.h"
#include "Model\Map.h"


CSaveBinary::CSaveBinary()
{
}


CSaveBinary::~CSaveBinary()
{
}

bool CSaveBinary::DoSerializeGame( const GDModel::CMap& map )
{
	QFile file("MapFile.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);

	for( int row = 0; row < map.GetMapItems().size(); row++ )
	{
		for( int col = 0;  col < map.GetMapItems().at(row).size(); col++ )
		{
			out << map.GetMapItems().at(row).begin();
		}
	}

	return false;
}

bool CSaveBinary::DoDeserializeGame( GDModel::CMap& map )
{
	return false;
}
