#include "stdafx.h"
#include "Nation.h"
#include "ProvinceItem.h"

Nation::Nation( const QString& id, const QString& filePath )
	: m_ID(id),
	m_FilePath(filePath),
	m_Color(Qt::white)
{
}

Nation::Nation()
	: m_ID("-"),
	m_FilePath("-"),
	m_Color(Qt::white)
{

}

Nation::Nation( const Nation& rhs )
	: m_ID(rhs.m_ID),
	m_FilePath(rhs.m_FilePath),
	m_Color(rhs.m_Color)
{

}

Nation::~Nation()
{
}

Nation& Nation::operator=( const Nation& rhs )
{
	m_ID = rhs.m_ID;
	m_FilePath = rhs.m_FilePath;
	m_Translations = rhs.m_Translations;
	m_Color = rhs.m_Color;
	return *this;
}

const QString& Nation::GetFilePath() const
{
	return m_FilePath;
}

const QString& Nation::GetID() const
{
	return m_ID;
}

void Nation::AttachProvince( ProvinceItem *province )
{
	if( province == nullptr )
	{
		return;
	}
	if( m_Provinces.find(province->m_ID) != m_Provinces.end() )
	{
		return;
	}
	m_Provinces.insert(province->m_ID,province);
}

const QColor& Nation::GetColor() const
{
	return m_Color;
}

void Nation::SetColor( const QColor& obj )
{
	m_Color = obj;
}

int Nation::CalcIC() const
{
	int result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::industry.GetName() ).GetData().toDouble();
	}
	return result;
}

int Nation::CalcPoints() const
{
	int result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::points.GetName() ).GetData().toDouble();
	}
	return result;
}

double Nation::CalcEnergy() const
{
	double result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::energy.GetName() ).GetData().toDouble();
	}
	return result;
}

double Nation::CalcMetal() const
{
	double result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::metal.GetName() ).GetData().toDouble();
	}
	return result;

}

double Nation::CalcCrudeOil() const
{
	double result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::crude_oil.GetName() ).GetData().toDouble();
	}
	return result;

}

double Nation::CalcRareMaterial() const
{
	double result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::rare_materials.GetName() ).GetData().toDouble();
	}
	return result;
}

double Nation::CalcManpower() const
{
	double result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::manpower.GetName() ).GetData().toDouble();
	}
	return result;
}

double Nation::CalcLeadership() const
{
	double result = 0;
	QHash<int,ProvinceItem*>::ConstIterator i;
	for( i = m_Provinces.constBegin(); i != m_Provinces.constEnd();i++ )
	{
		result += (*i)->FindItem( ProvinceItemPrototypeRepository::leadership.GetName() ).GetData().toDouble();
	}
	return result;
}
