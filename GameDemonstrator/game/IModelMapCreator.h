#ifndef IMAPCREATOR_H
#define IMAPCREATOR_H

class ModelMapRepository;

class IModelMapCreator
{
public:
	/** */
	virtual bool CreateMap() = 0;
	virtual ModelMapRepository* GetMap() = 0;
};

#endif // IMAPCREATOR_H