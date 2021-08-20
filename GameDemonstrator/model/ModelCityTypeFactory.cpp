#include "stdafx.h"
#include "ModelCityTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelCityType.h"
#include "DomElementFinder.h"
#include "DomValueExtractor.h"
#include "ModelCityTypeXMLItems.h"
#include "ModelCityTypeRepository.h"
#include "ModelConfigurationHeaderXMLItems.h"
#include "io\ConfigFileLoader.h"

ModelCityTypeFactory::ModelCityTypeFactory()
{
}

ModelCityTypeFactory::~ModelCityTypeFactory()
{
}

bool ModelCityTypeFactory::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelCityTypeXMLItems::CONFIG_FILE_NAME, ModelCityTypeXMLItems::ROOT_NAME))
	{
		return false;
	}

	ModelCityTypeRepository::GetInstance()->Init();

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelCityTypeRepository::GetInstance()->RegisterType(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("ModelCityTypes registered: " + QString::number(ModelCityTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelCityType* ModelCityTypeFactory::CreateFromXML( const QDomNode& node )
{
	int ownerTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_ID, ownerTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("CityType has not element of name: %1").arg(ModelCityTypeXMLItems::SUBELEMENT_ID));
		return nullptr;
	}

	ModelCityType *newOwnerType = new ModelCityType( ownerTypeId );
	bool allElementsExtracted = true;
	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_NAME, newOwnerType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_PICTURENAME, newOwnerType->PictureName);
		allElementsExtracted &= AttacheImage(newOwnerType);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_EFFICIENCY, newOwnerType->Efficiency);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_SPECIALIZED, newOwnerType->SpezializedUnitType);
	}

	if (false == allElementsExtracted)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(ModelCityTypeXMLItems::SUBELEMENT_ID).arg(QString::number(ownerTypeId)));
		delete newOwnerType;
		return nullptr;
	}

	return newOwnerType;
}

const QImage* ModelCityTypeFactory::LoadImage(const QString& path)
{
	QImage* newImage = new QImage;
	try
	{
		if (newImage->load(path) == false)
		{
			delete newImage;
			return nullptr;
		}
		return newImage;
	}
	catch (...)
	{
		delete newImage;
		return nullptr;
	}
	return newImage;
}

bool ModelCityTypeFactory::AttacheImage(ModelCityType* ModelCityType)
{
	QString pictureName(ModelCityType->GetPictureName());
	const QImage *terrainTypeImage = LoadImage(pictureName);

	if (terrainTypeImage == nullptr)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("Unable to load owner image: %1").arg(pictureName));
		return false;
	}

	ModelCityType->SetImage(terrainTypeImage);
	return true;

}
