#pragma once

namespace jha
{
class LogManager;
class LogManagerThreadContainer;

class LogFactory
{
public:
/** Initialisiert Logsystem */
	bool Init ();
/** Löscht alle erzeugt Instanzen */
	void CleanUp();
/** Erzeugt LogManager */
	LogManager* GetLogManager();
private:
	friend class LogInterface;
	static LogManager *m_LogManager;
	static LogManagerThreadContainer *m_LogManagerThread;
};

}

