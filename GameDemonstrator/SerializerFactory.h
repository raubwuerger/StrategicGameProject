#pragma once

class CSerializerInterface;
#include <QVector>

class CSerializerFactory
{
public:
/** */
	CSerializerFactory();
/** */
	~CSerializerFactory();
/** */
	void Release();
/** */
	CSerializerInterface* CreateInterface( QAction *action );
private:
	static CSerializerInterface* Interfaces;
};
