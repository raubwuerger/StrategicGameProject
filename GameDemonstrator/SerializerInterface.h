#pragma once

/** Serialisiert Spieldaten ... */

namespace GDModel { class CMap; }

class CSerializerInterface : public QObject
{
public:
	Q_OBJECT;
public:
	/** */
	CSerializerInterface();
	/** */
	virtual ~CSerializerInterface();
	/** */
	static void SetMap( const GDModel::CMap* map );
public slots:
	/** */
	virtual bool SerializeMap();
	/** */
	virtual bool DeserializeMap();
private:
	/** */
	virtual bool DoSerializeMap( const GDModel::CMap& map ) = 0;
	/** */
	virtual bool DoDeserializeMap( GDModel::CMap& map ) = 0;
private:
	friend class CGameFactory;
	static const GDModel::CMap *Map;
};

