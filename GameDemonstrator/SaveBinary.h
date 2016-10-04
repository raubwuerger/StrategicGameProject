#pragma once

#include "serializerinterface.h"

class CSaveBinary :	public CSerializerInterface
{
public:
	/** */
	CSaveBinary();
	/** */
	~CSaveBinary();
private:
	/** */
	virtual bool DoSerializeMap( const GDModel::CMap& map );
	/** */
	virtual bool DoDeserializeMap( GDModel::CMap& map );
};

