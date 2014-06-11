#pragma once

class HoI3Token
{
public:
	HoI3Token( const QString& name, const QString& value )
		: m_Name(name),
		m_Value(value)
	{

	}
	HoI3Token( const HoI3Token& rhs )
		: m_Name(rhs.m_Name),
		m_Value(rhs.m_Value),
		m_Tokens(rhs.m_Tokens)
	{
	}
	bool operator==( const HoI3Token& rhs )
	{
		if( m_Name != rhs.m_Name )
		{
			return false;
		}
		if( m_Value != rhs.m_Value )
		{
			return false;
		}
	}
public:
	QList<HoI3Token>	m_Tokens;
	QString		m_Name;
	QString		m_Value;
};


class HoI3Script
{
public:
	HoI3Script( const QString& name )
		: m_Name(name)
	{
	}
public:
	QList<HoI3Token> m_TokenList;
private:
	QString	m_Name;
};

class HoI3Scriptparser
{
public:
/** */
	HoI3Scriptparser();
/** */
	~HoI3Scriptparser();
/** */
	bool Parse( const QStringList &lines, HoI3Script& script );
private:
/** */
	QStringList CreateFlatTokenList( const QStringList &lines ) const;
/** */
	QString RemoveIgnoreData( const QString& line ) const;
/** */
	QStringList SeparateToken( const QString& line ) const;
/** */
	bool CreateScriptStructure( const QStringList& flatTokenList, QList<HoI3Token>& tokenList ) const;
/** */
	bool CreateTokenTree( const QStringList& flatTokenList, QStringList::ConstIterator& iterator, QList<HoI3Token>& tokenList ) const;
private:
	const QString ASSIGN;
	const QString SEPARATOR;
	const QString BLOCK_START;
	const QString BLOCK_END;
	const QString IGNORE_START;
};

