#ifndef SERIALIZERFACTORY_H
#define SERIALIZERFACTORY_H

class SerializerGame;
class GameDemonstrator;

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
