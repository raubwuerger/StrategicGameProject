#pragma once
/** @stereotype Strategie*/
class CGameMode
{
public:
	/** */
	CGameMode();
	/** */
	~CGameMode();
	/** */
	virtual void Activate() = 0;
	/** */
	virtual void Deavtivate() = 0;
};



