#ifndef ITEMTYPEBASE_H
#define ITEMTYPEBASE_H

//================================================================================
class ItemData
{
public:
	/** */
	ItemData();
	/** */
	ItemData( const QString& name );
	/** */
	ItemData( const QString& name, const QVariant& data );
	/** Get m_Name */
	const QString& GetName() const;
	/** Set m_Name */
	void SetName( const QString& val);
	/** Get m_Data */
	const QVariant& GetData() const;
	/** Set m_Data */
	void SetData( const QVariant& val);
	/** Get m_ValueActive */
	bool GetValueActive() const;
	/** */
	bool IsNull() const;
private:
	QString		m_Name;
	QVariant	m_Data;
	bool		m_ValueActive;
};

//================================================================================
class ItemTypeBase
{
public:
	/** Constructor */
	ItemTypeBase( const QString& id );
	/** Liefert Name */
	const QString& GetItemID() const;
	/** Liefert alle ItemDatas */
	const QMap<QString,ItemData>& GetItemMap() const;
	/** Fügt neues Item hinzu */
	bool AppendItemData( const QString& key, const ItemData& value );
	/** */
	ItemData FindItem( const QString& key ) const;
	/** Fügt neuen Wert altem hinzu. Macht nur Sinn bei QStringList ... */
	bool UpdateItem( const QString& key, const QVariant& data );
	/** Ersetzt alten Wert durch neuen */
	bool SetItem( const QString& key, const QVariant& data );
private:
	QString					m_ItemID;
	QMap<QString,ItemData>	m_Items;
};

//================================================================================
class ItemPrototypeRepository
{
public:
	/** */
	virtual void Init() = 0;
	/** Erzeugt ein Item aus name und data */	
	ItemData CreateItemData( const QString& name, const QString& data ) const;
	/** */
	void InitWithAllPrototypes( ItemTypeBase& baseType ) const;
protected:
	static QMap<QString,ItemData> m_PrototypeMap;
};

#endif // ITEMTYPEBASE_H
