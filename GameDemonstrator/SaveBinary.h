#pragma once

#include "serializerinterface.h"

class CSaveBinary :	public CSerializerInterface
{
public:
	/** */
	CSaveBinary( QAction *action );
	/** */
	~CSaveBinary();
	/** */
	virtual bool SerializeMap( const GDModel::CMap& map );
	/** */
	virtual bool DeserializeMap( GDModel::CMap& map );
};

