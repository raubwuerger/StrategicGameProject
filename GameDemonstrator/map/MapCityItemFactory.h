#ifndef MAPCITYITEMFACTORY_H
#define MAPCITYITEMFACTORY_H

class GameCityItem;
class MapView;

class MapCityItemFactory
{
public:
	/** */
	bool Create( MapView* mapView );
	/** */
	bool Create(MapView* mapView, const GameCityItem* gameCityItem);
private:
	/** */
	const QImage* GetImage(const GameCityItem* gameCityItem);
};

#endif // MAPCITYITEMFACTORY_H