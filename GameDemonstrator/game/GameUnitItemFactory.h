#ifndef GAMEUNITITEMFACTORY_H
#define GAMEUNITITEMFACTORY_H

class QDomNode;

/** Creates game map representation */
class GameUnitItemFactory
{
public:
	/** */
	GameUnitItemFactory();
	/** */
	~GameUnitItemFactory();
	/** */
	bool CreateGameUnitItemFromScratch();
	/** */
	bool CreateGameUnitItemsFromSaveGame( const QDomNode unitItemElements );
};

#endif  //GAMEUNITITEMFACTORY_H
