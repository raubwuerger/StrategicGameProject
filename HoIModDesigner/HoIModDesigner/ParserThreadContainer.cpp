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
 	connect(m_Parser, SIGNAL(Finished()), this, SLOT(HasFinished()) );
	connect(this, SIGNAL(Start()),m_Parser,SLOT(Parse()) );

	connect(m_Parser, SIGNAL(Finished()), &m_WorkerThread, SLOT(quit()));
//	connect(m_Parser, SIGNAL(Finished()), m_Parser, SLOT(deleteLater()));	//Wenn diese Connection aktiv ist, sind die Zeiger auf die Parser-childs (context) zerstört! Das Objekt lebt aber noch
//	connect(&m_WorkerThread, SIGNAL(finished()), &m_WorkerThread, SLOT(deleteLater())); //Wenn diese Connection aktiv ist, dann bekomme ich beim Beenden des Threads eine exception

	m_WorkerThread.start();
	emit Start();
	return true;
}

void ParserThreadContainer::HasFinished()
{
	m_Finished = true;
//jha: Geht nicht, das muss das verschobene Threadobjekt selber machen!
//	m_Parser->moveToThread(QApplication::instance()->thread());
	emit ParsingFinished();
}

bool ParserThreadContainer::GetFinished() const
{
	return m_Finished;
}
