#pragma once

class Nation
{
public:
/** */
	Nation( const QString& id, const QString& filePath );
/** */
	Nation( const Nation& rhs );
/** */
	~Nation();
/** */
	Nation& operator=( const Nation& rhs );
/** */
	const QString& GetFilePath() const;
/** */
	const QString& GetID() const;
protected:
	friend class HoIModDesigner;
/** */
	Nation();
private:
	QString	m_ID;
	QString	m_FilePath;
	QVector<QString> m_Translations;
};

