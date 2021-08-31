#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class MapUnitItem;

/** */
class GameController : public QObject
{
	Q_OBJECT
public:
	/** */
	GameController();
	/** */
	void Init();
public slots:
	/** */
	void SlotGameUnitSelected(int gameUnitId);
	/** */
	void SlotGameUnitUnselected(int gameUnitId);
private:
	MapUnitItem*	Selected;
};

#endif // GAMECONTROLLER_H