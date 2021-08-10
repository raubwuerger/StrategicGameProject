#ifndef SerializerInterface_H
#define SerializerInterface_H

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
public slots:
	/** */
	bool SlotSaveGame();
private:
	QString CreateSaveGameFileName() const;
private:
	friend class SerializerFactory;
	ISerializeGameInterface* SerializeGameInterface;
};

#endif

