#include "stdafx.h"
#include "Nation.h"


Nation::Nation( const QString& id, const QString& filePath )
	: m_ID(id),
	m_FilePath(filePath)
{
}

Nation::Nation()
	: m_ID("-"),
	m_FilePath("-")
{

}

Nation::Nation( const Nation& rhs )
	: m_ID(rhs.m_ID),
	m_FilePath(rhs.m_FilePath)
{

}

Nation::~Nation()
{
}

Nation& Nation::operator=( const Nation& rhs )
{
	m_ID = rhs.m_ID;
	m_FilePath = rhs.m_FilePath;
	m_Translations = rhs.m_Translations;
	return *this;
}

const QString& Nation::GetFilePath() const
{
	return m_FilePath;
}

const QString& Nation::GetID() const
{
	return m_ID;
}
