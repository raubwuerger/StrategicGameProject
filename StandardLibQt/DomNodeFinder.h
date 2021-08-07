#ifndef DOMNODEFINDER_H
#define DOMNODEFINDER_H

class QDomNode;

class DomNodeFinder
{
public:
	/** */
	DomNodeFinder( const QDomNode& domNode );
	/** */
	const QDomNode FindDomeNodeByName( const QString& childName );
	/** */
	const QDomNode FindDomeNodeByNameClone( const QString& childName );
private:
	const QDomNode& DomeNode;
};

#endif