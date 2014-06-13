#pragma once

#include <QThread>
class ParserHoI3;

class ParserThreadContainer : public QObject
{
	Q_OBJECT
public:
/** Constructor */
	ParserThreadContainer( ParserHoI3 *parser );
/** */
	bool StartParsing();
/** */
	bool GetFinished() const;
public slots:
/** */
	void HasFinished();
signals:
/** */
	void Start();
/** */
	void ParsingFinished();
private:
	QThread		m_WorkerThread;
	bool		m_Finished;
	ParserHoI3	*m_Parser;
};
