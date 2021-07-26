#pragma once

#include "serializerinterface.h"

class CSaveToXML : public CSerializerInterface
{
public:
/** */
	CSaveToXML();
/** */
	~CSaveToXML();
private:
	/** */
	virtual bool DoSerializeGame( const GDModel::GameMap& gameMap );
	/** */
	virtual bool DoDeserializeGame( GDModel::GameMap& gameMap );

};

