#ifndef HOI3CONTEXT_H
#define HOI3CONTEXT_H

class ProvinceGraphicsPixmapItem;
class ProvinceItem;
class ExtendedGraphicsScene;
class ExtendedGraphicsView;
class Nation;
class BuildingItem;

class HoI3Context
{
public:
	HoI3Context( const QString& basePath );
	~HoI3Context();
	QString GetPathProvinceBMP() const;
	QString GetPathDefinitionCSV() const;
	QString GetPathCountriesTXT() const;
	QString GetPathBuildingsTXT() const;
	QVector<QString> GetPathProvincesDir() const;
	QVector<QString> GetPathCommonDir() const;
	void UpdateNationColor( ProvinceItem *province );
public:
	QHash<int,ProvinceItem*> m_ProvinceMap;
	QHash<QString,Nation*>	m_Countries;
	QHash<QString,BuildingItem*> m_BuildingTypes;
	const QString TRAIL;
	QString		m_BasePath;
	QString		m_PathTFH;
	QString		m_ModPath;
	QString		m_DefinitionCSV;
	QString		m_CountriesTXT;
	QString		m_ProvincesDir;
	QString		m_ProvincesBMP;
	QString		m_UsedMod;
	QString		m_CommonDir;
	QString		m_BuildingsTXT;
};
#endif // HOI3CONTEXT_H
