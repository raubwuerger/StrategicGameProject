#pragma once

#include <QThread>
class ParserHoI3;

class ParserThreadContainer : public QObject
{
	Q_OBJECT
public:
/** Constructor */
	ParserThreadContainer();
private:
	QThread		m_WorkerThread;
	ParserHoI3	*m_Parser;
};
