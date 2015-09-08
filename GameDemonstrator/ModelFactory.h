#pragma once

namespace GDModel
{

class CMap;

class CModelFactory
{
public:
	/** */
	CModelFactory();
	/** */
	~CModelFactory();
	/** */
	void CreateEmptyMap( int rows, int cols,  CMap* map );
};

}