#ifndef GAMEOWNERTYPEFACTORY_H
#define GAMEOWNERTYPEFACTORY_H

class QDomNode;
class GameOwnerItem;
class ModelOwnerType;

class GameOwnerItemFactory
{
public:
	/** */
	bool Create();
	/** */
	bool Create(const QDomNode node);
private:
	/** */
	GameOwnerItem* CreateItemFromXML(const QDomNode& node);
	/** */
	GameOwnerItem* CreateItem(const ModelOwnerType* model);
};

#endif // GAMEOWNERTYPEFACTORY_H