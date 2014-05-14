#pragma once

namespace jha
{
class LogManager;
class BaseThread;

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
	static LogManager *m_LogManager;
	static BaseThread *m_LogManagerThread; //Wohl eher einen eigenen LogManagerThread erstellen
};

}

