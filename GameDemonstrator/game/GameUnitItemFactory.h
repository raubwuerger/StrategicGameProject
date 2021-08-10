#ifndef GAMEUNITITEMFACTORY_H
#define GAMEUNITITEMFACTORY_H

class QDomNode;
class GameUnitItem;

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
private:
	/** */
	bool CreateUnitItems(const QDomNode& units);
	/** */
	GameUnitItem* CreateUnitItemFromXML(const QDomNode& unit);

};

#endif  //GAMEUNITITEMFACTORY_H
