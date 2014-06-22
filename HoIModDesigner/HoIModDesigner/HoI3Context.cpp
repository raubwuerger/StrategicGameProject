#include "stdafx.h"
#include "HoI3Context.h"

HoI3Context::HoI3Context( const QString& basePath ) 
	: m_BasePath(basePath),
	m_PathTFH("tfh"),
	m_ProvincesBMP("map\\provinces.bmp"),
	m_DefinitionCSV("map\\definition.csv"),
	m_CountriesTXT("common\\countries.txt"),
	m_ProvincesDir("history\\provinces"),
	m_ModPath("mod\\RandomHoI"),
	m_CommonDir("common\\"),
	TRAIL("\\"),
	m_BuildingsTXT("common\\buildings.txt")
{

}

QString HoI3Context::GetPathProvinceBMP() const
{
	return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ProvincesBMP;
}

QString HoI3Context::GetPathDefinitionCSV() const
{
	return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_UsedMod +m_DefinitionCSV;
}

QString HoI3Context::GetPathCountriesTXT() const
{
	return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_CountriesTXT;
}

QString HoI3Context::GetPathBuildingsTXT() const
{
	return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_BuildingsTXT;
}

QVector<QString> HoI3Context::GetPathProvincesDir() const
{
	QVector<QString> paths;
	// 		paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ProvincesDir);
	// 		paths.push_back(m_BasePath +TRAIL +m_ProvincesDir);
	paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_ProvincesDir);
	return paths;
}

QVector<QString> HoI3Context::GetPathCommonDir() const
{
	QVector<QString> paths;
	// 		paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_CommonDir);
	// 		paths.push_back(m_BasePath +TRAIL +m_ProvincesDir);
	paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_CommonDir);
	return paths;
}

#include "ProvinceItem.h"
#include "Nation.h"
void HoI3Context::UpdateNationColor( ProvinceItem *province )
{
	if( province == nullptr )
	{
		return;
	}
	QString controller = province->FindItem( ProvinceItemPrototypeRepository::controller.GetName() ).GetData().toString();
	QHash<QString,Nation*>::iterator country = m_Countries.find(controller);
	if( country == m_Countries.end() )
	{
		return;
	}
	(*country)->AttachProvince(province);
	province->m_ColorNation = (*country)->GetColor();
}

HoI3Context::~HoI3Context()
{
	int who_kills_me = 0;
}
