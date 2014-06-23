#pragma once
#include <QString>

namespace jha
{

class Command
{
public:
/** Constructor */
	Command( const QString& name );
/** */
	virtual ~Command();
/** */
	bool Execute();
/** Get m_Name */
	const QString& GetName() const;
private:
/**  */
	virtual bool DoExecute() = 0;
private:
	QString	m_Name;
};

}