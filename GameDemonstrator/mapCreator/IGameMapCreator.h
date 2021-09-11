#ifndef IGAMEMAPCREATOR
#define IGAMEMAPCREATOR

static int MapTileId = 0;

class IGameMapCreator
{
public:
	/** */
	virtual bool CreateMap() = 0;
};

#endif // IGAMEMAPCREATOR