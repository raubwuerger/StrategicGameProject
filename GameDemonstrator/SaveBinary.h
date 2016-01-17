#pragma once

#include "serializerinterface.h"

class CSaveBinary :	public CSerializerInterface
{
public:
	/** */
	CSaveBinary();
	/** */
	~CSaveBinary();
	/** */
	virtual bool SerializeMap( const GDModel::CMap& map );
	/** */
	virtual bool DeserializeMap( GDModel::CMap& map );
};

