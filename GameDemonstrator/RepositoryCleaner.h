#ifndef REPOSITORYCLEANER_H
#define REPOSITORYCLEANER_H

class BaseRepository;

class RepositoryCleaner
{
public:
	/** */
	static RepositoryCleaner* GetInstance();
	/** */
	void Register(BaseRepository* baseRepository);
	/** */
	void ReleaseAll();
private:
	static RepositoryCleaner*	Instance;
	QVector<BaseRepository*>	Repositories;
};

#endif // REPOSITORYCLEANER_H