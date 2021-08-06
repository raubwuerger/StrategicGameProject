#ifndef SerializerFactory_H
#define SerializerFactory_H

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

#endif
