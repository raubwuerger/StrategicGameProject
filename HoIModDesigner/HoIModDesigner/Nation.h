#pragma once

class ProvinceItem;

class Nation
{
public:
/** */
	Nation( const QString& id, const QString& filePath );
/** */
	Nation( const Nation& rhs );
/** */
	~Nation();
/** */
	Nation& operator=( const Nation& rhs );
/** */
	const QString& GetFilePath() const;
/** */
	const QString& GetID() const;
/** */
	void AttachProvince( ProvinceItem *province );
/** */
	const QColor& GetColor() const;
/** */
	void SetColor( const QColor& obj );
/** */
	int CalcIC() const;
/** */
	int CalcPoints() const;
/** */
	double CalcEnergy() const;
/** */
	double CalcMetal() const;
/** */
	double CalcCrudeOil() const;
/** */
	double CalcRareMaterial() const;
/** */
	double CalcManpower() const;
/** */
	double CalcLeadership() const;
protected:
	friend class ParserHoI3;
/** */
	Nation();
public:
	QColor	m_Color;
	QString	m_ID;
	QString	m_FilePath;
	QVector<QString> m_Translations;
	QHash<int,ProvinceItem*>	m_Provinces;
};

