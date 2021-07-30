#include "stdafx.h"
#include "GameDemonstratorConfig.h"
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include <QDomNode>

QString GameDemonstratorConfig::RootName = "GameDemonstrator";
QString GameDemonstratorConfig::NodeLogging = "Logging";
QString GameDemonstratorConfig::NodeLoggingGlobalLogLevel = "GlobalLogLevel";

QString GameDemonstratorConfig::GlobalLogLevel = "";
