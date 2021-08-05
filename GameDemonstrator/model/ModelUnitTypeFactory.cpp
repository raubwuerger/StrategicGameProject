#include "stdafx.h"
#include "ModelUnitTypeFactory.h"
#include "ModelUnitType.h"
#include "ModelUnitTypeRepository.h"
#include "ModelUnitTypeXMLItems.h"
#include "ModelConfigurationHeaderXMLItems.h"
#include "DomValueExtractor.h"
#include <QtXml>
#include "LogInterface.h"

ModelUnitTypeFactory::ModelUnitTypeFactory()
{

}

ModelUnitTypeFactory::~ModelUnitTypeFactory()
{

}

bool ModelUnitTypeFactory::Create()
{
	ModelUnitTypeXMLItems config;
	jha::GetLog()->Log_MESSAGE(QObject::tr("Loading %1 from file: %2").arg(config.ROOT_NAME).arg(config.CONFIG_FILE_NAME));
	QFile file(config.CONFIG_FILE_NAME);
	if (false == OpenFile(&file))
	{
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;

	if (domDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn) == false)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr));
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if (root.tagName() != config.ROOT_NAME)
	{
		jha::GetLog()->Log(QObject::tr("The file is not an %1 file.").arg(config.ROOT_NAME), jha::LOGLEVEL::LL_WARNING);
		return false;
	}

	if (root.hasAttribute(ModelConfigurationHeaderXMLItems::VERSION) && root.attribute(ModelConfigurationHeaderXMLItems::VERSION) != ModelConfigurationHeaderXMLItems::VERSION_NUMBER)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("The file is not an %1 file.").arg(config.ROOT_NAME));
		return false;
	}

	QDomNodeList terrainTypeNodes = root.childNodes();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelUnitTypeRepository::GetInstance()->RegisterModelUnit( CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("TerrainTypes registered: " + QString::number(ModelUnitTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

bool ModelUnitTypeFactory::OpenFile(QFile* file)
{
	if (file->open(QFile::ReadOnly | QFile::Text) == false)
	{
		jha::GetLog()->Log(QObject::tr("Cannot read file %1:\n%2.").arg(file->fileName()).arg(file->errorString()), jha::LOGLEVEL::LL_WARNING);
		return false;
	}
	return true;
}

ModelUnitType* ModelUnitTypeFactory::CreateFromXML(const QDomNode& node)
{
	ModelUnitTypeXMLItems config;
	int unitTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(config.SUBELEMENT_ID, unitTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("ModelTerrainType has not element of name: %1").arg(config.SUBELEMENT_ID));
		return nullptr;
	}

	ModelUnitType *newUnitType = new ModelUnitType(unitTypeId);

	bool allElementsExtracted = true;
	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_NAME, newUnitType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_PICTURENAME, newUnitType->PicturePath);
		allElementsExtracted &= AttacheImage(newUnitType);
	}

	if (false == allElementsExtracted)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(config.SUBELEMENT_ID).arg(QString::number(unitTypeId)));
		delete newUnitType;
		return nullptr;
	}
	return newUnitType;
}

bool ModelUnitTypeFactory::AttacheImage(ModelUnitType* modelUnit)
{
	QString imageName(modelUnit->GetPicturePath());
	const QImage *image = LoadImage(imageName);

	if (image == nullptr)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("Unable to load terrain image: %1").arg(imageName));
		return false;
	}

	modelUnit->SetImage(image);
	return true;
}

const QImage* ModelUnitTypeFactory::LoadImage(const QString& path)
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

