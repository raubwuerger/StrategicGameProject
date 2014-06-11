#include "stdafx.h"
#include "HoI3Scriptparser.h"


HoI3Scriptparser::HoI3Scriptparser()
	:	ASSIGN("="),
	SEPARATOR(" "),
	BLOCK_START("{"),
	BLOCK_END("}"),
	IGNORE_START("#")
{
}


HoI3Scriptparser::~HoI3Scriptparser()
{
}

bool HoI3Scriptparser::Parse( const QStringList &lines, HoI3Script& script )
{
	if( lines.empty() == true )
	{
		return false;
	}
	QStringList flatTokenList = CreateFlatTokenList( lines );
	if( flatTokenList.isEmpty() == true )
	{
		return false;
	}

	CreateScriptStructure(flatTokenList,script.m_TokenList);
	return false;
}

QStringList HoI3Scriptparser::CreateFlatTokenList( const QStringList &lines ) const
{
	QStringList token;

	for( int i=0;i<lines.size();i++ )
	{
		if( lines.at(i).isEmpty() == true )
		{
			continue;
		}
		if( lines.at(i).at(0) == IGNORE_START )
		{
			continue;
		}
		QString line = RemoveIgnoreData(lines.at(i));
		token.append( SeparateToken(line) );
	}

	return token;
}

QString HoI3Scriptparser::RemoveIgnoreData( const QString& line ) const
{
	int foundIndex = line.indexOf(IGNORE_START);
	if( foundIndex == -1 )
	{
		return line;
	}
	return line.left(foundIndex);
}

QStringList HoI3Scriptparser::SeparateToken( const QString& line ) const
{
	QStringList rawToken = line.split(SEPARATOR,QString::SkipEmptyParts);
	QStringList token;
	for( int i=0; i<rawToken.size();i++ )
	{
		QString tokenString = rawToken.at(i).trimmed();
		if( tokenString.isEmpty() == true )
		{
			continue;
		}
		token.append(tokenString);
	}
	return token;
}

bool HoI3Scriptparser::CreateScriptStructure( const QStringList& flatTokenList, QList<HoI3Token>& tokenList ) const
{
	if( flatTokenList.isEmpty() == true )
	{
		return false;
	}
	if( flatTokenList.at(0) == ASSIGN || flatTokenList.at(0) == BLOCK_END )
	{
		return false;
	}
	QStringList::ConstIterator tokenPosition = flatTokenList.constBegin();
	return CreateTokenTree( flatTokenList, tokenPosition, tokenList );
	
}

bool HoI3Scriptparser::CreateTokenTree( const QStringList& flatTokenList, QStringList::ConstIterator& tokenPosition, QList<HoI3Token>& tokenList ) const
{
	while( tokenPosition != flatTokenList.constEnd() )
	{
		QString tokenName = *tokenPosition;
		tokenPosition++;

		if( tokenName == BLOCK_END )
		{
			return true;
		}

		if( *tokenPosition != ASSIGN )
		{
			//LOG: Bad Token. "=" expected after lhs!
			return false;
		}
		tokenPosition++;

		if( *tokenPosition == ASSIGN || *tokenPosition == BLOCK_END )
		{
			//LOG: Bad Token. Not expected after "="!
			return false;
		}
		if( *tokenPosition == BLOCK_START )
		{
			tokenPosition++;
			HoI3Token newToken(tokenName,"");
			if( CreateTokenTree(flatTokenList,tokenPosition,newToken.m_Tokens) == false )
			{
				return false;
			}
			tokenList.append(newToken);
		}
		else
		{
			HoI3Token newToken(tokenName,*tokenPosition);
			tokenList.append(newToken);
			tokenPosition++;
		}
	}
	return true;
}
