#ifndef BASEREPOSITORY_H
#define BASEREPOSITORY_H

class BaseRepository
{
public:
	/** */
	BaseRepository();
	/** */
	virtual bool Init() = 0;
	/** */
	virtual void Release() = 0;
};

#endif // BASEREPOSITORY_H