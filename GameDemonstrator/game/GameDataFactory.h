#ifndef GAMEDATAFACTORY_H
#define GAMEDATAFACTORY_H

class QDomNode;

class GameDataFactory
{
public:
	/** */
	bool Init();
	/** */
	bool Create();
	/** */
	bool CreateGameDataFromSaveGame(const QDomNode& node);
};

#endif // GAMEDATAFACTORY_H