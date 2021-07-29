#include "stdafx.h"
#include "ModelOwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelOwnerType.h"
#include "DomElementFinder.h"
#include "DomValueExtractor.h"
#include "ModelOwnerTypeConfig.h"
#include "ModelOwnerTypeRepository.h"

ModelOwnerTypeFactory*	ModelOwnerTypeFactory::Instance = nullptr;

ModelOwnerTypeFactory* ModelOwnerTypeFactory::GetInstance()
{
	if( nullptr != Instance ) 
	{
		return Instance;
	}

	Instance = new ModelOwnerTypeFactory;
	return Instance;
}

ModelOwnerTypeFactory::ModelOwnerTypeFactory()
{
}

ModelOwnerTypeFactory::~ModelOwnerTypeFactory()
{
}

bool ModelOwnerTypeFactory::Create()
{
	ModelOwnerTypeConfig config;
	jha::GetLog()->Log_MESSAGE("Loading OwnerTypes from file: " +config.ConfigFilePath);
	QFile file(config.ConfigFilePath);
	if( false == OpenFile(&file) )
	{
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;


	if( domDocument.setContent(&file, true, &errorStr, &errorLine,&errorColumn) == false ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr) );
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if( root.tagName() != config.RootName ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("The file is not an %1 file.").arg(config.RootName) );
		return false;
	}

	if (root.hasAttribute( config.Version ) && root.attribute( config.Version ) != config.VersionNumber ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("The file is not an %1 version %2 file.").arg(config.RootName).arg(config.VersionNumber) );
		return false;
	}

	QDomNodeList ownerTypeNodes = root.childNodes();
	for( int i=0; i <ownerTypeNodes.count(); i++ )
	{
		ModelOwnerType *tempModelOwnerType = CreateFromXML( ownerTypeNodes.at(i) );
		if( nullptr != tempModelOwnerType )
		{
			ModelOwnerTypeRepository::GetInstance()->RegisterOwnerType( tempModelOwnerType );
		}
	}

	int modelTypesRegistered = ModelOwnerTypeRepository::GetInstance()->GetCount();
	if( modelTypesRegistered <= 0 )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("No OwnerTypes have been registered!"));
	}
	else
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("OwnerTypes registered: %1").arg( QString::number(modelTypesRegistered) ));
	}
	return true;
}

bool ModelOwnerTypeFactory::OpenFile( QFile* file  )
{
	if( file->open(QFile::ReadOnly | QFile::Text) == false )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Cannot read file %1:\n%2.").arg(file->fileName()).arg(file->errorString()) );
		return false;
	}
	return true;
}

ModelOwnerType* ModelOwnerTypeFactory::CreateFromXML( const QDomNode& node )
{
	ModelOwnerTypeConfig config;
	int ownerTypeId = 0;

	DomValueExtractor extractor(node);
	if( false == extractor.ExtractValue(config.SubelementId,ownerTypeId) )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("OwnerType has not element of name: %1").arg(config.SubelementId) );
		return nullptr;
	}

	ModelOwnerType *newOwnerType = new ModelOwnerType( ownerTypeId );
	bool allExtracted = true;
	{
		DomValueExtractor extractor(node);
		allExtracted &= extractor.ExtractValue(config.SubelementName,newOwnerType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allExtracted &= extractor.ExtractValue(config.SubelementPicturePath,newOwnerType->PicturePath);
	}

	{
		DomValueExtractor extractor(node);
		allExtracted &= extractor.ExtractValue(config.SubelementColor,newOwnerType->Color);
	}

	if( false == allExtracted )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Unable to register %1 with id %2").arg(config.SubelementId).arg(QString::number(ownerTypeId)) );
		delete newOwnerType;
		return nullptr;
	}

	return newOwnerType;
}
