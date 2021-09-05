#include "stdafx.h"
#include "DomNodeListPrinter.h"
#include "LogInterface.h"
#include <QtXml>

bool DomNodeListPrinter::Print(const QDomNodeList& domNodeList)
{
	if (true == domNodeList.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNodeList has no child elements"));
		return false;
	}

	QVector<QString> nodeNames;
	for (int nodeIndex = 0; nodeIndex < domNodeList.count(); nodeIndex++)
	{
		QDomNode currentNode = domNodeList.at(nodeIndex);
		QString nodeName = currentNode.nodeName();
		nodeNames.push_back(nodeName);
		jha::GetLog()->Log_DEBUG(QObject::tr("Node name at index: %1 - %2").arg(nodeName).arg(QString::number(nodeIndex)));
		Print(currentNode.childNodes());
	}
	return true;
}
