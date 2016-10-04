#pragma once

namespace GDModel
{

class CMap;
class CGameInitialisationData;

class CModelFactory
{
public:
	/** */
	CModelFactory();
	/** */
	~CModelFactory();
	/** */
	void CreateEmptyMap( const GDModel::CGameInitialisationData& data, CMap** map );
};

}