#ifndef DOMNODELISTFINDER_H
#define DOMNODELISTFINDER_H

class QDomNodeList;
class QDomNode;

//================================================================================
class DomNodeListFinder
{
public:
/** */
	DomNodeListFinder( const QDomNodeList& domNodeList );
/** */
	QDomNode FindDomNodeByName( const QString& domNodeName );
private:
	const QDomNodeList& DomNodeList;
};

#endif // DOMNODELISTFINDER_H
