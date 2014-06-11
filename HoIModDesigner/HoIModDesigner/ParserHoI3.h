#pragma once

class HoI3Context;
class ProvinceItem;
class Nation;
class ProvinceGraphicsPixmapItem;
class ExtendedGraphicsScene;
class HoI3Script;

class ParserHoI3
{
public:
/** */
	ParserHoI3();
/** */
	bool Parse( HoI3Context& context, ExtendedGraphicsScene *scene );
/** */
	HoI3Script* ParseScript( const QString& filename ) const;
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
	bool SortLinesByTimeline( const QStringList& data, QVector<QStringList>& timeLineParts ) const;
/** */
	bool CreateTokenMap( const QStringList& line, QHash<QString,QString> &tokens, const QString& separator = "=" ) const;
/** */
	bool CreateProvinceTimeLineData( const QHash<QString,QString>& tokens, ProvinceItem* data ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, int& valueToUpadte ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, double& valueToUpadte ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, QString& valueToUpadte ) const;
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
};

