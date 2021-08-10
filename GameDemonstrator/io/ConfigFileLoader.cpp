#include "stdafx.h"
#include "ConfigFileLoader.h"
#include "LogInterface.h"
#include "model\ModelConfigurationHeaderXMLItems.h"

ConfigFileLoader::ConfigFileLoader()
{

}

bool ConfigFileLoader::LoadConfig(const QString& filename, const QString& rootName)
{
	if (true == filename.isEmpty())
	{
		return false;
	}

	jha::GetLog()->Log_MESSAGE(QObject::tr("Loading config file: %1").arg(filename));
	QFile file(filename);
	if (false == OpenFile(&file))
	{
		return false;
	}
	return LoadXMLDocument(file,rootName);
}

const QDomNodeList& ConfigFileLoader::GetQDomNodeList() const
{
	return DomNodeList;
}

bool ConfigFileLoader::OpenFile(QFile* file)
{
	if (file->open(QFile::ReadOnly | QFile::Text) == false)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Cannot read file %1:\n%2.").arg(file->fileName()).arg(file->errorString()));
		return false;
	}
	return true;
}

bool ConfigFileLoader::LoadXMLDocument(QFile& file, const QString& rootName)
{
	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;


	if (domDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn) == false)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr));
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if (root.tagName() != rootName)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("The file is not an %1 file.").arg(rootName));
		return false;
	}

	if (root.hasAttribute(ModelConfigurationHeaderXMLItems::VERSION) && root.attribute(ModelConfigurationHeaderXMLItems::VERSION) != ModelConfigurationHeaderXMLItems::VERSION_NUMBER)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("The file is not an %1 version %2 file.").arg(rootName).arg(ModelConfigurationHeaderXMLItems::VERSION_NUMBER));
		return false;
	}

	DomNodeList = root.childNodes();
	file.close();
	return true;
}
