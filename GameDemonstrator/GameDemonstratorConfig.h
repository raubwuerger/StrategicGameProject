#pragma once
class QDomElement;
class QDomNode;
class QDomNodeList;

class GameDemonstratorConfig
{
public:
	static QString GlobalLogLevel;
private:
	friend class GameDemonstratorFactory;
	static QString RootName;
	static QString NodeLogging;
	static QString NodeLoggingGlobalLogLevel;
};