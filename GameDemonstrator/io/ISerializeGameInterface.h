#ifndef ISERIALIZEGAMEINTERFACE_H
#define ISERIALIZEGAMEINTERFACE_H

class ISerializeGameInterface
{
public:
	/** */
	virtual bool SaveGame( const QString& saveGameName ) = 0;
	/** */
	virtual bool LoadGame( const QString& saveGameName ) = 0;
};

#endif // ISERIALIZEGAMEINTERFACE_H