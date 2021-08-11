#ifndef ModelMapFactory_H
#define ModelMapFactory_H

class GameMapRepository;
class IGameMapCreator;

/** Creates game map representation */
class GameMapFactory
{
public:
	/** */
	GameMapFactory();
	/** */
	~GameMapFactory();
	/** */
	void Release();
	/** Creates Map */
	bool Create();
private:
	GameMapRepository*		TheGameMap;
	IGameMapCreator*		MapCreator;
};

#endif
