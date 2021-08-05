#ifndef SerializeBinary_H
#define SerializeBinary_H

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

#endif

