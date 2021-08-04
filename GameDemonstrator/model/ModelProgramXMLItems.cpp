#include "stdafx.h"
#include "ModelProgramXMLItems.h"
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include <QDomNode>

const QString ModelProgramXMLItems::ROOT_NAME = "GameDemonstrator";
const QString ModelProgramXMLItems::NODE_LOGGING = "Logging";
const QString ModelProgramXMLItems::SUBELEMENT_GLOBAL_LOG_LEVEL = "GlobalLogLevel";

QString ModelProgramXMLItems::GlobalLogLevel = "";
