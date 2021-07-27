#pragma once

class SerializerInterface;
#include <QVector>

class SerializerFactory
{
public:
/** */
	SerializerFactory();
/** */
	~SerializerFactory();
/** */
	void Release();
/** */
	SerializerInterface* CreateInterface();
private:
	static SerializerInterface* SerializerInterfaceInstanze;
};
