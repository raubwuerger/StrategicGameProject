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
	virtual bool DoSerializeGame( const GDModel::CMap& map );
	/** */
	virtual bool DoDeserializeGame( GDModel::CMap& map );
};

