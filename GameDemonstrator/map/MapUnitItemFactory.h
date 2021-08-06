#ifndef MapViewUnitItemFactory_H
#define MapViewUnitItemFactory_H

class MapUnitItem;

/** Creates game map representation */
class MapUnitItemFactory
{
	/** */
	MapUnitItemFactory();
	/** */
	~MapUnitItemFactory();
	/** */
	bool Create() {}
	/** */
	MapUnitItem* CreateDummyUnitItem();
};

#endif
