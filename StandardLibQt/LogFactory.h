#pragma once

namespace jha
{
class LoggingWorker;
class LoggingThread;
class Logger;

class LogFactory
{
public:
/** */
	static LogFactory* GetInstance();
/** Initialisiert Logsystem */
	bool Init( bool startLogging = true );
/** L�scht alle erzeugt Instanzen */
	void Release();
/** Registriert einen neuen Logger. �bernimmt Besitz! */
	bool RegisterLogger( jha::Logger* logger );
/** */
	void Enable();
/** */
	void Disable();
/** */
	bool GetEnabled() const;
private:
/** Default constructor */
	LogFactory();
/** Copy constructor */
	LogFactory( const LogFactory& );
private:
	static LogFactory* Instance;
	static LoggingWorker *LoggingWorkerObject;
	static LoggingThread *LoggingThreadObject;
};

}

