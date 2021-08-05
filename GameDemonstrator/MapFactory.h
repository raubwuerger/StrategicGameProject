#ifndef MapFactory_H
#define MapFactory_H

class CreateNewMap;
class MapView;

/** @stereotype factory*/
class MapFactory
{
public:
	/** */
	static MapFactory* GetInstance();
	/** */
	void Release();
	/** */
	void SetMapView( MapView* mapView );
	/** */
	void SetParent( QObject *parent );
	/** */
	CreateNewMap* CreateNewMapFunction();
private:
	/** */
	MapFactory();
	/** */
	~MapFactory();
private:
	static MapFactory* Instance;
	CreateNewMap* TheCreateNewMap;
	MapView		*MapViewInstance;
	QObject		*Parent;
};

#endif

