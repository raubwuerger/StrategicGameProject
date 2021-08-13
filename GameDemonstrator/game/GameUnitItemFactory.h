#ifndef GAMEUNITITEMFACTORY_H
#define GAMEUNITITEMFACTORY_H

class QDomNode;
class GameUnitItem;
class ModelUnitType;

/** Creates game map representation */
class GameUnitItemFactory
{
public:
	/** */
	GameUnitItemFactory();
	/** */
	~GameUnitItemFactory();
	/** */
	GameUnitItem* CreateGameUnitItemFromScratch(const ModelUnitType* modelUnitType, int gameMapItemId);
	/** */
	bool CreateGameUnitItemsFromSaveGame( const QDomNode unitItemElements );
private:
	/** */
	bool CreateUnitItems(const QDomNode& units);
	/** */
	GameUnitItem* CreateUnitItemFromXML(const QDomNode& unit);
	/** */
	int CreateId();
	/** */
	QString CreateName(const ModelUnitType* modelUnitType) const;
};

#endif  //GAMEUNITITEMFACTORY_H
