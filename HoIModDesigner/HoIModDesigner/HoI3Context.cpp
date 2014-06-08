#include "stdafx.h"
#include "HoI3Context.h"

HoI3Context::HoI3Context() : m_BasePath("E:\\Spiele\\HoI3"),
	m_PathTFH("tfh"),
	m_ProvincesBMP("map\\provinces.bmp"),
	m_DefinitionCSV("map\\definition.csv"),
	m_CountriesTXT("common\\countries.txt"),
	m_ProvincesDir("history\\provinces"),
	m_ModPath("mod\\RandomHoi"),
	m_CommonDir("common\\"),
	TRAIL("\\")
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
	//return m_BasePath +TRAIL +m_CountriesTXT;
	return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_CountriesTXT;
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
