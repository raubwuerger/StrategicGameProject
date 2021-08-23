#ifndef BASEREPOSITORY_H
#define BASEREPOSITORY_H

class BaseRepository
{
public:
	/** */
	BaseRepository();
	/** */
	virtual void Release() = 0;
};

#endif // BASEREPOSITORY_H