#ifndef MAPCITYITEMFACTORY_H
#define MAPCITYITEMFACTORY_H

class GameCity;
class MapView;

class MapCityItemFactory
{
public:
	/** */
	bool Create(MapView* mapView);
	/** */
	bool Create(MapView* mapView, const GameCity* gameCityItem);
private:
	/** */
	const QImage* GetImage(const GameCity* gameCityItem);
};

#endif // MAPCITYITEMFACTORY_H