#ifndef DOMNODEFINDER_H
#define DOMNODEFINDER_H
class QDomNode;

/**
	Sucht alle Kindknoten nach dem �bergebnen Namen und liefert dies Kind zur�ck
	<Name>
		<SubNode>Text</Subnode>
	</Name>
*/

//================================================================================
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