#pragma once

class CSerializerInterface;
#include <QVector>

class CSerializerFactory
{
public:
/** */
	CSerializerFactory();
/** */
	~CSerializerFactory();
/** */
	void Release();
/** */
	CSerializerInterface* CreateInterface();
private:
	static CSerializerInterface* SerializerInterface;
};
