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
/** F�hrt Kommando aus */
	bool Execute();
/** F�hrt Undo aus */
	bool Undo();
/** Get m_Name */
	const QString& GetName() const;
/** */
	virtual bool operator==( const Command& rhs ) const;
private:
/**  */
	virtual bool DoExecute() = 0;
/** */
	virtual bool DoUndo();
private:
	QString	m_Name;
};

}