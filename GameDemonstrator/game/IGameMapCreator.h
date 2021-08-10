#ifndef IMAPCREATOR_H
#define IMAPCREATOR_H

class GameMapRepository;

class IGameMapCreator
{
public:
	/** */
	virtual bool CreateMap() = 0;
	virtual GameMapRepository* GetMap() = 0;
};

#endif // IMAPCREATOR_H