#pragma once

class QDomNode;

class DomNodeFinder
{
public:
	/** */
	DomNodeFinder( const QDomNode& domNode );
	/** */
	const QDomNode* FindDomeNodeByName( const QString& childName );
	/** */
	const QDomNode FindDomeNodeByNameClone( const QString& childName );
private:
	const QDomNode& DomeNode;
};