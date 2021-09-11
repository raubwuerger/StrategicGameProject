#ifndef GAMEOWNERTYPEFACTORY_H
#define GAMEOWNERTYPEFACTORY_H

class QDomNode;
class GameOwner;
class ModelOwnerType;

class GameOwnerFactory
{
public:
	/** */
	bool Create();
	/** */
	bool Create(const QDomNode node);
private:
	/** */
	GameOwner* CreateFromXML(const QDomNode& node);
	/** */
	GameOwner* CreateGameOwner(const ModelOwnerType* model);
};

#endif // GAMEOWNERTYPEFACTORY_H