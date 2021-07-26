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
	virtual bool DoSerializeGame( const GDModel::CMap& map );
	/** */
	virtual bool DoDeserializeGame( GDModel::CMap& map );

};

