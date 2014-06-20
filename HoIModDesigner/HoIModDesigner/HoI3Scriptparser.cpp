#include "stdafx.h"
#include "HoI3Scriptparser.h"


HoI3Scriptparser::HoI3Scriptparser()
	:	ASSIGN("="),
	SEPARATOR(" "),
	BLOCK_START("{"),
	BLOCK_END("}"),
	COMMENT("#"),
	LINEEND("\n"),
	TAB("\t")
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

		QString line = lines.at(i);
		if( lines.at(i).at(0) != COMMENT )
		{
			line = RemoveIgnoreData(line);
		}
		
		token.append( SeparateToken(line) );
	}

	return token;
}

QString HoI3Scriptparser::RemoveIgnoreData( const QString& line ) const
{
	int foundIndex = line.indexOf(COMMENT);
	if( foundIndex == -1 )
	{
		return line;
	}
	return line.left(foundIndex);
}

QStringList HoI3Scriptparser::SeparateToken( const QString& line ) const
{
	if( line.isEmpty() == true )
	{
		return QStringList();
	}

	QStringList token;
	if( line.at(0) == COMMENT )
	{
		token.append(line);
		return token;
	}

	//TODO: Hier sollten auch noch die #Kommentare erkannt werden ...
	QStringList rawToken = line.split(SEPARATOR,QString::SkipEmptyParts);
	QString tokenInBrakets;
	for( int i=0; i<rawToken.size();i++ )
	{
		QString tokenString = rawToken.at(i).trimmed();
		if( tokenString.isEmpty() == true )
		{
			continue;
		}
		
		if( tokenString.count("\"") == 1 )
		{
			if( tokenInBrakets.isEmpty() == true )
			{
				tokenInBrakets = tokenString;
				continue;
			}
			else
			{
				tokenInBrakets += tokenString;
				tokenString = tokenInBrakets;
				tokenInBrakets.clear();
			}
		}
		else if( tokenInBrakets.isEmpty() == false )
		{
			tokenInBrakets += tokenString;
			continue;
		}
//		token.append(tokenString.remove("\""));
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

		if( *tokenPosition == ASSIGN ) //TODO: Bei geöffneter Klammer können auch nur Werte kommen
		{
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
				if( tokenName.at(0) == COMMENT )
				{
					newToken.m_Comment = true;
				}
				if( CreateTokenTree(flatTokenList,tokenPosition,newToken.m_Tokens) == false )
				{
					return false;
				}
				tokenList.append(newToken);
			}
			else
			{
				HoI3Token newToken(tokenName,*tokenPosition);
				if( tokenName.at(0) == COMMENT )
				{
					newToken.m_Comment = true;
				}
				tokenList.append(newToken);
				tokenPosition++;
			}
		}
		else
		{
			if( *tokenPosition == BLOCK_START )
			{
				//SOwas gibt es nicht { <Wert> } ...
				return false;
			}
			HoI3Token newToken("",tokenName); //Muss wohl eine Aufreihung von Werten sein ...
			if( tokenName.at(0) == COMMENT )
			{
				newToken.m_Comment = true;
			}
			tokenList.append(newToken);
		}
	}
	return true;
}

#include "std\LogInterface.h"
bool HoI3Scriptparser::SaveScript( const HoI3Script& script, const QString& alternatePath /*= "" */ ) const
{
	QString fileName( script.GetName() );
	if( alternatePath.isEmpty() == false )
	{
		fileName = alternatePath;
	}
	QFile file(fileName); 
	if( file.open(QIODevice::WriteOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to open file: " +fileName, LEVEL::LL_ERROR);
		return nullptr;
	}

	QTextStream stream(&file);
	QList<HoI3Token>::ConstIterator iter;
	for( iter = script.m_TokenList.constBegin(); iter != script.m_TokenList.constEnd(); iter++ )
	{
		if( iter->m_Comment == true )
		{
			stream << iter->m_Value << LINEEND;
			continue;
		}
		WriteTokenToStream( (*iter), stream, 1, true, false );
		stream << BLOCK_END << LINEEND << LINEEND;
	}

	file.close();
	return true;
}

void HoI3Scriptparser::WriteTokenToStream( const HoI3Token& token, QTextStream& stream, int tabLevel, bool lineEnd, bool checkBlockEnd ) const
{
	QString value(token.m_Value);
	if( value.isEmpty() == true )
	{
		value = BLOCK_START;
	}
	bool groupInOneRow = false;
	if( token.m_Tokens.size() == 1 || token.m_Tokens.size() == 2 )
	{
		groupInOneRow = true;
	}

	stream << token.m_Name << SEPARATOR << ASSIGN << SEPARATOR << value << (groupInOneRow == true || lineEnd == false ? SEPARATOR : LINEEND);

	QList<HoI3Token>::ConstIterator iter;
	for( iter = token.m_Tokens.constBegin(); iter != token.m_Tokens.constEnd(); iter++ )
	{
		if( groupInOneRow == false )
		{
			for( int i=0;i<tabLevel;i++ )
			{
				stream << TAB;
			}
		}
		WriteTokenToStream( (*iter), stream, tabLevel + 1, !groupInOneRow );
	}
	if( token.m_Tokens.isEmpty() == true || checkBlockEnd == false )
	{
		return;
	}
	if( groupInOneRow == false )
	{
		for( int i=1;i<tabLevel;i++ )
		{
			stream << TAB;
		}
	}
	stream << BLOCK_END << LINEEND;
}

bool HoI3Scriptparser::IsDateToken( const HoI3Token& token ) const
{
	return token.m_Name.count( "." ) == 2;
}
