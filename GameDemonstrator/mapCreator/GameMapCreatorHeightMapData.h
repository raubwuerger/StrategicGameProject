#ifndef GAMEMAPCREATORHEIGHTMAPDATA_H
#define GAMEMAPCREATORHEIGHTMAPDATA_H

struct GameMapCreatorHeightMapData
{
	int		MapSizeX = -1;
	int		MapSizeY = -1;

	double LowerXBound = -1.0;
	double UpperXBound = -1.0;
	double LowerZBound = -1.0;
	double UpperZBound = -1.0;

	int		OctaveCount = -1;
	double	Frequency = -1.0;
	double	Persistence = -1.0;
};

#endif // GAMEMAPCREATORHEIGHTMAPDATA_H

/*
int		MapSizeX = NOT_INITIALIZED_INT;
int		MapSizeY = NOT_INITIALIZED_INT;

double LowerXBound = NOT_INITIALIZED_DOUBLE;
double UpperXBound = NOT_INITIALIZED_DOUBLE;
double LowerZBound = NOT_INITIALIZED_DOUBLE;
double UpperZBound = NOT_INITIALIZED_DOUBLE;

int		OctaveCount = NOT_INITIALIZED_INT;
double	Frequency = NOT_INITIALIZED_DOUBLE;
double	Persistence = NOT_INITIALIZED_DOUBLE;
*/