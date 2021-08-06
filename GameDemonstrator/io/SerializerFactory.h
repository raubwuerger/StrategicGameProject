#ifndef SerializerFactory_H
#define SerializerFactory_H

class ConnectorSaveGame;
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
	ConnectorSaveGame* CreateInterface();
private:
	static ConnectorSaveGame* SerializerInterfaceInstanze;
};

#endif
