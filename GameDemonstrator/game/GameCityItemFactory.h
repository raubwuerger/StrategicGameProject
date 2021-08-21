#ifndef GAMECITYITEMFACTORY_H
#define GAMECITYITEMFACTORY_H

class QDomNode;
class GameCityItem;
class ModelOwnerType;


/** Creates game map representation */
class GameCityItemFactory
{
public:
	/** */
	GameCityItemFactory();
	/** */
	~GameCityItemFactory();
	/** */
	bool Create( const QDomNode cityItemElements );
private:
	/** */
	bool CreateItems(const QDomNode& city);
	/** */
	GameCityItem* CreateItemFromXML(const QDomNode& city);
	/** */
	int CreateId();
};

#endif  //GAMECITYITEMFACTORY_H
