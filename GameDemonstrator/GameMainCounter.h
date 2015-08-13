#ifndef GAMECOUNTER_H
#define GAMECOUNTER_H

#include <QObject>

class GameMainCounter : public QObject
{
	Q_OBJECT

public:
	/** */
	GameMainCounter(QObject *parent);
	/** */
	~GameMainCounter();
	/** */
	void Increment();
	/** Get GameDate */	
	const QDate& GetGameDate() const { return GameDate; }
private:
	QDate	GameDate;
	int		MonthIncrement;
};

#endif // GAMECOUNTER_H
