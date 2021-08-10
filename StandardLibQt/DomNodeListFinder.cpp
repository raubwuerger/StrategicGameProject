#include "stdafx.h"
#include "DomNodeListFinder.h"
#include <QDomNodeList>
#include "LogInterface.h"


DomNodeListFinder::DomNodeListFinder( const QDomNodeList& domNodeList )
	: DomNodeList(domNodeList)
{

}

QDomNode DomNodeListFinder::FindDomNodeByName(const QString& domNodeName)
{
	int count = DomNodeList.count();
	for (int index = 0; index < count; index++)
	{
		if (DomNodeList.at(index).nodeName() != domNodeName)
		{
			continue;
		}
		return DomNodeList.at(index);
	}
	jha::GetLog()->Log_WARNING(QObject::tr("Unable to find DomNode: %1").arg(domNodeName));
	return QDomNode();
}
