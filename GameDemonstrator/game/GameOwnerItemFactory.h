#ifndef GAMEOWNERTYPEFACTORY_H
#define GAMEOWNERTYPEFACTORY_H

class QDomNode;
class GameOwnerItem;

class GameOwnerItemFactory
{
public:
	/** */
	bool CreateItemsFromSaveGame(const QDomNode node);
private:
	/** */
	GameOwnerItem* CreateItemFromXML(const QDomNode& node);
};

#endif // GAMEOWNERTYPEFACTORY_H