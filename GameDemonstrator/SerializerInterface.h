#pragma once

/** Serializes game data ... */
class ISerializeGameInterface;

class CSerializerInterface : public QObject
{
public:
	Q_OBJECT;
public:
	/** */
	CSerializerInterface();
	/** */
	virtual ~CSerializerInterface();
public slots:
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();
private:
	friend class CSerializerFactory;
	ISerializeGameInterface* SerializeGameInterface;
};

