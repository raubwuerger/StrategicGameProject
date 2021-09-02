#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class MapUnitItem;

/** */
class GameController : public QObject //TODO -> Rename to GameUnitController
{
	Q_OBJECT
public:
	/** */
	GameController();
	/** */
	void Init();
	/** */
	void ConnectSinglePlayer();
	/** */
	void ConnectEditor();
	/** */
	void Disconnect();
	/** */
	bool InitGame();
public slots:
	/** */
	void SlotGameUnitSelected(int gameUnitId);
	/** */
	void SlotGameUnitUnselected(int gameUnitId);
	/** */
	void SlotGameUnitSelectedEditorMode(int gameUnitId);
private:
	/** */
	bool IsUnitOfItsOwn(const MapUnitItem* mapUnitItem) const;
private:
	friend class GameModeController;
	MapUnitItem*		Selected;
};

#endif // GAMECONTROLLER_H