#ifndef SerializerFactory_H
#define SerializerFactory_H

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

#endif
