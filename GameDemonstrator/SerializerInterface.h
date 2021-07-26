#pragma once

/** Serialisiert Spieldaten ... */

namespace GDModel { class GameMap; }

class CSerializerInterface : public QObject
{
public:
	Q_OBJECT;
public:
	/** */
	CSerializerInterface();
	/** */
	virtual ~CSerializerInterface();
	/** */
	static void SetMap( const GDModel::GameMap* gameMap );
public slots:
	/** */
	virtual bool SerializeGame();
	/** */
	virtual bool DeserializeGame();
private:
	/** */
	virtual bool DoSerializeGame( const GDModel::GameMap& gameMap ) = 0;
	/** */
	virtual bool DoDeserializeGame( GDModel::GameMap& gameMap ) = 0;
private:
	friend class CGameFactory;
	static const GDModel::GameMap *TheGameMap;
};

