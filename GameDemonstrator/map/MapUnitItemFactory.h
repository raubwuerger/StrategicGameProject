#ifndef MapViewUnitItemFactory_H
#define MapViewUnitItemFactory_H

class MapUnitItem;

/** Creates game map representation */
class MapUnitItemFactory
{
public:
	/** */
	static MapUnitItemFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	MapUnitItem* CreateDummyUnitItem();
private:
	/** */
	MapUnitItemFactory();
	/** */
	~MapUnitItemFactory();
private:
	static MapUnitItemFactory	*Instance;
};

#endif
