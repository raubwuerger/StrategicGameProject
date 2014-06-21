#pragma once

class HoI3Context;
class ProvinceItem;
class Nation;
class ProvinceGraphicsPixmapItem;
class ExtendedGraphicsScene;
class HoI3Script;
class BuildingItem;

class HoI3Context;
class ParserHoI3 : public QObject
{
	Q_OBJECT
public:
/** */
	ParserHoI3( ExtendedGraphicsScene *scene, HoI3Context *context );
/** */
	HoI3Script* ParseScript( const QString& filename ) const;
public slots:
/** */
	void Parse();
signals:
	void Finished();
private:
/** */
	QPixmap* LoadProvincesBMP( const QString& fileName );
/** */
	bool ParseProvinzList( QHash<int,ProvinceItem*>& mapRGB, QHash<int,ProvinceItem*>& mapID, const QString& provincePath ) const;
/** */
	int ParseToLines( const QByteArray& data, QStringList &lines ) const;
/** */
	ProvinceItem* CreateProvinzeItemFromString( const QString& line ) const;
/** */
	bool ParseCountryList( QHash<QString,Nation*>& countryList, const QString& countryPath, const QVector<QString>& pathCountryDetails ) const;
/** */
	Nation* CreateCountryFromString( const QString& line ) const;
/** */
	bool ParseCountryDetailInfo( const QString& filename, Nation* provinceItem ) const;
/** */
	bool ParseProvinceDetailInfoDirectory( QHash<int,ProvinceItem*>& provinzList, const QString& provincePath ) const;
/** */
	int CreateProvinceIDFromFilename( const QString& filename, const QString& separator = "-" ) const;
/** */
	bool ParseProvinceDetailInfo( const QString& filename, ProvinceItem* provinceItem ) const;
/** */
	void AttachProvincesToNations( const QHash<int,ProvinceItem*>& provinces, QHash<QString,Nation*>& nations );
/** */
	void AttachProvinceToNation( ProvinceItem *province, QHash<QString,Nation*>& nations );
/** */
	bool CreateColorMap( QHash<int,ProvinceItem*>& result, const QPixmap* pixmap );
/** */
	void CreateGraphicsItems( QHash<int,ProvinceItem*>& result, ExtendedGraphicsScene *scene ) const;
/** */
	ProvinceGraphicsPixmapItem* CreateItemFromPixelClash( const QPolygon& pixelClash, const QPolygon& pixelClashContour, const QColor& color, ExtendedGraphicsScene *scene ) const;
/** */
	bool ParseBuildingsTXT( QHash<QString,BuildingItem*>& buildingList, const QString& filename ) const;
public:
	HoI3Context				*m_Context;
	ExtendedGraphicsScene	*m_Scene;
};

