#ifndef IMAPCREATOR_H
#define IMAPCREATOR_H

class ModelMapRepository;

class IMapCreator
{
public:
	/** */
	virtual bool CreateMap() = 0;
	virtual ModelMapRepository* GetMap() = 0;
};

#endif // IMAPCREATOR_H