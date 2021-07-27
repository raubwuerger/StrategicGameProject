#pragma once

/** Serializes game data ... */
class ISerializeGameInterface;

class SerializerInterface : public QObject
{
public:
	Q_OBJECT;
public:
	/** */
	SerializerInterface();
	/** */
	virtual ~SerializerInterface();
public slots:
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();
private:
	friend class SerializerFactory;
	ISerializeGameInterface* SerializeGameInterface;
};

