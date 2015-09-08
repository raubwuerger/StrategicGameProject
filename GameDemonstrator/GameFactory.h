#pragma once

class CGameInitialisationData;

/** Erstellt alle Komponenten die f�r ein neuen Spiel notwendig sind */
class CGameFactory
{
public:
	/** */
	CGameFactory();
	/** */
	~CGameFactory();
	/** */
	void CreateNewGame( const CGameInitialisationData& data );
private:
	/** */
	void CreateModel( const CGameInitialisationData& data );
};

