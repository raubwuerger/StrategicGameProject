#ifndef GAMECOUNTER_H
#define GAMECOUNTER_H

class GameMainCounter
{
public:
	/** */
	static GameMainCounter* GetInstance();
	/** */
	void Increment();
	/** Get GameDate */	
	const QDate& GetCurrentDate() const;
private:
	/** */
	GameMainCounter();
	/** */
	~GameMainCounter();
private:
	friend class GameConnector;
	QDate	CurrentDate;
	QDate	StartDate;
	int		MonthIncrement;
	static GameMainCounter* Instance;
};

#endif // GAMECOUNTER_H
