#pragma once

#include "ISerializeGameInterface.h"

class SerializeBinary : public ISerializeGameInterface
{
public:
	/** */
	SerializeBinary();
	/** */
	~SerializeBinary();
	/** */
	bool SaveGame( const QString& saveGameName );
	/** */
	bool LoadGame( const QString& saveGameName );
};

