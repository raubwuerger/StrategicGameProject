#include "stdafx.h"
#include "ModelOwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelOwnerType.h"
#include "DomElementFinder.h"
#include "DomValueExtractor.h"
#include "ModelOwnerTypeXMLItems.h"
#include "ModelOwnerTypeRepository.h"
#include "ModelConfigurationHeaderXMLItems.h"
#include "io\ConfigFileLoader.h"
#include "ImageLoader.h"

ModelOwnerTypeFactory::ModelOwnerTypeFactory()
{
}

ModelOwnerTypeFactory::~ModelOwnerTypeFactory()
{
}

bool ModelOwnerTypeFactory::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelOwnerTypeXMLItems::CONFIG_FILE_NAME, ModelOwnerTypeXMLItems::ROOT_NAME))
	{
		return false;
	}

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelOwnerTypeRepository::GetInstance()->RegisterOwnerType(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("ModelOwnerTypes registered: " + QString::number(ModelOwnerTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelOwnerType* ModelOwnerTypeFactory::CreateFromXML( const QDomNode& node )
{
	int ownerTypeId = 0;
	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(ModelOwnerTypeXMLItems::SUBELEMENT_ID, ownerTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("OwnerType has not element of name: %1").arg(ModelOwnerTypeXMLItems::SUBELEMENT_ID));
		return nullptr;
	}

	ModelOwnerType *newType = new ModelOwnerType( ownerTypeId );
	bool allElementsExtracted = true;
	allElementsExtracted &= extractor.ExtractValue(ModelOwnerTypeXMLItems::SUBELEMENT_NAME, newType->Name);
	allElementsExtracted &= extractor.ExtractValue(ModelOwnerTypeXMLItems::SUBELEMENT_PICTURENAME, newType->PictureName);
	allElementsExtracted &= extractor.ExtractValue(ModelOwnerTypeXMLItems::SUBELEMENT_COLOR, newType->Color);

	if( false == allElementsExtracted )
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(ModelOwnerTypeXMLItems::SUBELEMENT_ID).arg(QString::number(ownerTypeId)));
		delete newType;
		return nullptr;
	}

	allElementsExtracted &= AttacheImage(newType);
	return newType;
}

bool ModelOwnerTypeFactory::AttacheImage(ModelOwnerType* type)
{
	const QImage *terrainTypeImage = ImageLoader::LoadImage(type->GetPictureName());

	if (terrainTypeImage == nullptr)
	{
		return false;
	}

	type->SetImage(terrainTypeImage);
	return true;

}
