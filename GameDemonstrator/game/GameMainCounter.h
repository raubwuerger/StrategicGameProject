#ifndef GAMEMAINCOUNTER_H
#define GAMEMAINCOUNTER_H

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

#endif // GAMEMAINCOUNTER_H
