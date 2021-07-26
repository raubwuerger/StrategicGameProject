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
	virtual bool DoSerializeGame( const GDModel::GameMap& gameMap );
	/** */
	virtual bool DoDeserializeGame( GDModel::GameMap& gameMap );
};

