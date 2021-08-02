#include "stdafx.h"
#include "DomNodeFinder.h"
#include <QtXml>
#include "LogInterface.h"


DomNodeFinder::DomNodeFinder(const QDomNode& domNode)
	: DomeNode(domNode)
{

}

const QDomNode* DomNodeFinder::FindDomeNodeByName(const QString& childName)
{
	QDomNodeList childNodes = DomeNode.childNodes();
	if( true == childNodes.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNode <%1> has no childs!").arg(DomeNode.nodeName()) );
		return nullptr;
	}

	int childCount = childNodes.length();
	for( int childIndex = 0; childIndex < childCount; childIndex++ )
	{
		if( childNodes.at(childIndex).nodeName() != childName )
		{
			continue;
		}
		return &childNodes.at(childIndex);
	}

	jha::GetLog()->Log_WARNING( QObject::tr("QDomNode <%1> has no child with name: %2").arg(DomeNode.nodeName()).arg(childName) );
	return nullptr;
}

const QDomNode DomNodeFinder::FindDomeNodeByNameClone(const QString& childName)
{
	QDomNodeList childNodes = DomeNode.childNodes();
	if( true == childNodes.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNode <%1> has no childs!").arg(DomeNode.nodeName()) );
		return QDomNode();
	}

	int childCount = childNodes.length();
	for( int childIndex = 0; childIndex < childCount; childIndex++ )
	{
		if( childNodes.at(childIndex).nodeName() != childName )
		{
			continue;
		}
		return childNodes.at(childIndex).cloneNode(true);
	}

	jha::GetLog()->Log_WARNING( QObject::tr("QDomNode <%1> has no child with name: %2").arg(DomeNode.nodeName()).arg(childName) );
	return QDomNode();

}
