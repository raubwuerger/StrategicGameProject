#include "stdafx.h"
#include "ParserThreadContainer.h"
#include "ParserHoI3.h"

ParserThreadContainer::ParserThreadContainer( ParserHoI3 *parser )
	: m_Finished(false),
	m_Parser(parser)
{
}

bool ParserThreadContainer::StartParsing()
{
	if( m_Parser == nullptr )
	{
		return false;
	}
	m_Finished = false;
	m_Parser->moveToThread(&m_WorkerThread);
 	connect(&m_WorkerThread, &QThread::finished, m_Parser, &QObject::deleteLater);
//	connect(m_Parser, SIGNAL(Finished()), this, SLOT(HasFinished()), Qt::QueuedConnection );
	connect(m_Parser, SIGNAL(Finished()), this, SLOT(HasFinished()) );
	connect(this, SIGNAL(Start()),m_Parser,SLOT(Parse()) );
	m_WorkerThread.start();
	emit Start();
	return true;
}

void ParserThreadContainer::HasFinished()
{
	m_Finished = true;
	m_WorkerThread.quit();
//jha: Geht nicht, das muss das verschobene Threadobjekt selber machen!
//	m_Parser->moveToThread(QApplication::instance()->thread());
	emit ParsingFinished();
}

bool ParserThreadContainer::GetFinished() const
{
	return m_Finished;
}
