#ifndef IGAMEMAPCREATOR
#define IGAMEMAPCREATOR

class GameMapRepository;

class IGameMapCreator
{
public:
	/** */
	virtual bool CreateMap() = 0;
	virtual GameMapRepository* GetMap() = 0;
};

#endif // IGAMEMAPCREATOR