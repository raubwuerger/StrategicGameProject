#ifndef GAMEMAPREPOSITORY_H
#define GAMEMAPREPOSITORY_H

#include "BaseRepository.h"

class GameMapTile;

/** Repräsentiert die Karte im Speicher */
class GameMapTileRepository : public BaseRepository
{
public:
	/** */
	static GameMapTileRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** Get MapTiles */	
	const QVector< QVector<GameMapTile*> >* GetMapTiles() const;
	/** */
	void SetGameMapTiles( QVector< QVector<GameMapTile*>>* mapTiles );
	/** */
	int GetCols() const;
	/** */
	int GetRows() const;
	/** */
	GameMapTile* GetGameMapTile( unsigned int row, unsigned int col );
	/** */
	int GetGameMapTileId( unsigned int row, unsigned int col );
	/** */
	bool UpdateGameMapTile(const GameMapTile* gameMapTile);
	/** */
	GameMapTile* GetById( unsigned int id );
private:
	/** */
	GameMapTileRepository();
	/** */
	~GameMapTileRepository();
	/** */
	void UpdateIdToModelMapTile();
private:
	friend class GameMapTileFactory;
	QVector< QVector<GameMapTile*> >*	GameMapTiles;
	static GameMapTileRepository*		Instance;
	QMap<int, GameMapTile*>				IdToModelMapTile;
};

#endif // GAMEMAPREPOSITORY_H
