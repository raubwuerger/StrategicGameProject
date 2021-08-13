#ifndef SERIALIZERFACTORY_H
#define SERIALIZERFACTORY_H

class SerializerGame;
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
	SerializerGame* CreateInterface();
private:
	static SerializerGame* SerializerInterfaceInstanze;
};

#endif // SERIALIZERFACTORY_H
