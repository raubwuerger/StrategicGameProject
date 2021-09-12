#ifndef COMMANDCREATENEWGAME_H
#define COMMANDCREATENEWGAME_H

class CreateNewGameDialog;
class MapView;

class CommandCreateNewGame
{
public:
	/** */
	bool Create(MapView* mapView);
private:
	/** */
	void GetGameCreationData(const CreateNewGameDialog* dialog);
	/** */
	bool CreateNewGame(MapView* mapView);
};

#endif // COMMANDCREATENEWGAME_H