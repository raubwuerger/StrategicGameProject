#ifndef GAMECOUNTER_H
#define GAMECOUNTER_H

class GameMainCounter
{
public:
	/** */
	GameMainCounter();
	/** */
	~GameMainCounter();
	/** */
	void Increment();
	/** Get GameDate */	
	const QDate& GetGameDate() const;
private:
	QDate	GameDate;
	int		MonthIncrement;
};

#endif // GAMECOUNTER_H
