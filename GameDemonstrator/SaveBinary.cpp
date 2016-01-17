#include "stdafx.h"
#include "SaveBinary.h"
#include "Model\Map.h"


CSaveBinary::CSaveBinary()
{
}


CSaveBinary::~CSaveBinary()
{
}

bool CSaveBinary::SerializeMap( const GDModel::CMap& map )
{
	QFile file("MapFile.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);   // we will serialize the data into the file
	out << QString("the answer is");   // serialize a string
	out << (qint32)42;
	return false;
}

bool CSaveBinary::DeserializeMap( GDModel::CMap& map )
{
	return false;
}
