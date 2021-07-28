#include "stdafx.h"
#include "ModelOwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelOwnerType.h"
#include "XMLTools.h"
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
	jha::GetLog()->Log("Loading OwnerTypes from file: " +ModelOwnerTypeConfig().ConfigFilePath, LEVEL::LL_MESSAGE);
	QFile file;
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
		jha::GetLog()->Log( tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr), jha::LOGLEVEL::LL_WARNING );
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if( root.tagName() != ModelOwnerTypeConfig().RootName ) 
	{
		jha::GetLog()->Log( tr("The file is not an OwnerTypes file."), jha::LOGLEVEL::LL_WARNING );
		return false;
	}

	if (root.hasAttribute( ModelOwnerTypeConfig().Version ) && root.attribute( ModelOwnerTypeConfig().Version ) != ModelOwnerTypeConfig().VersionNumber ) 
	{
		jha::GetLog()->Log( tr("The file is not an OwnerTypes version 1.0 file."), jha::LOGLEVEL::LL_WARNING );
		return false;
	}

	QDomNodeList ownerTypeNodes = root.childNodes();
	for( int i=0; i <ownerTypeNodes.count(); i++ )
	{
		ModelOwnerTypeRepository::GetInstance()->RegisterOwnerType( CreateOwnerTypeFromXML( ownerTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("OwnerTypes registered: " +QString::number(ModelOwnerTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);
	return true;
}

bool ModelOwnerTypeFactory::OpenFile( QFile* file  )
{
	QString fileName( ModelOwnerTypeConfig().ConfigFilePath );

	file = new QFile(fileName);
	if( file->open(QFile::ReadOnly | QFile::Text) == false )
	{
		jha::GetLog()->Log( tr("Cannot read file %1:\n%2.").arg(fileName).arg(file->errorString()), jha::LOGLEVEL::LL_WARNING );
		return false;
	}
	return true;
}

ModelOwnerType* ModelOwnerTypeFactory::CreateOwnerTypeFromXML( const QDomNode& node )
{
	int ownerTypeId = 0;
	DomElementFinder finder(node);
	if( false == finder.TryFindElement( ModelOwnerTypeConfig().SubelementId, ownerTypeId ) )
	{
		jha::GetLog()->Log("OwnerType has not element of name: " +ModelOwnerTypeConfig().SubelementId, LEVEL::LL_WARNING);
		return nullptr;
	}

	ModelOwnerType *newOwnerType = new ModelOwnerType( ownerTypeId );

	if( false == finder.TryFindElement( ModelOwnerTypeConfig().SubelementName, newOwnerType->Name ) )
	{
		jha::GetLog()->Log("OwnerType has not element of name: " +ModelOwnerTypeConfig().SubelementName, LEVEL::LL_WARNING);
		return nullptr;
	}

	if( false == finder.TryFindElement( ModelOwnerTypeConfig().SubelementPicturePath, newOwnerType->PicturePath ) )
	{
		jha::GetLog()->Log("OwnerType has not element of name: " +ModelOwnerTypeConfig().SubelementPicturePath, LEVEL::LL_WARNING);
		return nullptr;
	}

	if( false == finder.TryFindElement( ModelOwnerTypeConfig().SubelementColor, newOwnerType->Color ) )
	{
		jha::GetLog()->Log("OwnerType has not element of name: " +ModelOwnerTypeConfig().SubelementColor, LEVEL::LL_WARNING);
		return nullptr;
	}

	return newOwnerType;
}
