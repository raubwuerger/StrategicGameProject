#ifndef SERIALIZERINTERFACE_H
#define SERIALIZERINTERFACE_H

/** Serializes game data ... */
class ISerializeGameInterface;

class SerializerGame : public QObject
{
public:
	Q_OBJECT;
public:
	/** */
	SerializerGame();
	/** */
	virtual ~SerializerGame();
	/** */
	bool LoadGame();
private:
	friend class SerializerFactory;
	ISerializeGameInterface* SerializeGameInterface;
};

#endif // SERIALIZERINTERFACE_H

