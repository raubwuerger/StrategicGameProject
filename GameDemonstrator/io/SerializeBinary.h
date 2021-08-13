#ifndef SERIALIZEBINARY_H
#define SERIALIZEBINARY_H

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

#endif // SERIALIZEBINARY_H

