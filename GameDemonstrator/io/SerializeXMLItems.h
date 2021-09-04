#ifndef SERIALIZEXMLITEMS_H
#define SERIALIZEXMLITEMS_H

class SerializeXMLItems
{
public:
	static const QString SAVEGAME;

	static const QString GAME;
	static const QString GAME_VERSION;
	static const QString GAME_PLAYERCOUNT;
	static const QString GAME_GAMETURN;

	static const QString PLAYERS;
	static const QString PLAYERS_PLAYER;
	static const QString PLAYER_ID;
	static const QString PLAYER_OWNERTYPEID;
	static const QString PLAYER_NAME;
	static const QString PLAYER_HUMAN;

	static const QString MAP;

	static const QString MAP_SETTINGS;
	static const QString MAP_SETTINGS_ROWS;
	static const QString MAP_SETTINGS_COLS;

	static const QString MAP_MAPITEMS;
	static const QString MAP_MAPITEM;
	static const QString MAP_ID;
	static const QString MAP_ROW;
	static const QString MAP_COL;
	static const QString MAP_TERRAINTYPE;

	static const QString UNITS;
	static const QString UNITS_UNIT;
	static const QString UNITS_ID;
	static const QString UNITS_UNITTYPEID;
	static const QString UNITS_GAMEMAPITEMID;
	static const QString UNITS_OWNERTYPEID;
	static const QString UNITS_NAME;
	static const QString UNITS_STRENGTH;
	static const QString UNITS_MOVEMENTPOINTS;

	static const QString CITIES;
	static const QString CITIES_CITY;
	static const QString CITIES_ID;
	static const QString CITIES_MODELCITYTYPEID;
	static const QString CITIES_NAME;
	static const QString CITIES_GAMEMAPITEMID;
	static const QString CITIES_OWNERTYPEID;
	static const QString CITIES_EFFICIENCY;
	static const QString CITIES_SPEZIALIZEDUNITTYPEID;
	static const QString CITIES_STRENGTH;

};

#endif // SERIALIZEXMLITEMS_H
