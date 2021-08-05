#ifndef ISerializeGameInterface_H
#define ISerializeGameInterface_H

class ISerializeGameInterface
{
public:
	/** */
	virtual bool SaveGame( const QString& saveGameName ) = 0;
	/** */
	virtual bool LoadGame( const QString& saveGameName ) = 0;
};

#endif