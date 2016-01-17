#pragma once

/** Serialisiert Spieldaten ... */

namespace GDModel { class CMap; }

class CSerializerInterface
{
public:
	/** */
	CSerializerInterface();
	/** */
	virtual ~CSerializerInterface();
	/** */
	virtual bool SerializeMap( const GDModel::CMap& map ) = 0;
	/** */
	virtual bool DeserializeMap( GDModel::CMap& map ) = 0;
};

