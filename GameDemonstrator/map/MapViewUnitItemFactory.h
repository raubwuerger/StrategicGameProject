#ifndef MapViewUnitItemFactory_H
#define MapViewUnitItemFactory_H

class MapViewUnitItem;

/** Creates game map representation */
class MapViewUnitItemFactory
{
public:
	/** */
	static MapViewUnitItemFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	MapViewUnitItem* CreateDummyUnitItem();
private:
	/** */
	MapViewUnitItemFactory();
	/** */
	~MapViewUnitItemFactory();
private:
	static MapViewUnitItemFactory	*Instance;
};

#endif
