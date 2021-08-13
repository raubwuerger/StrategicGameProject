#ifndef IGAMEMAPCREATOR
#define IGAMEMAPCREATOR

class GameMapItemRepository;

class IGameMapItemCreator
{
public:
	/** */
	virtual bool CreateMap() = 0;
};

#endif // IGAMEMAPCREATOR