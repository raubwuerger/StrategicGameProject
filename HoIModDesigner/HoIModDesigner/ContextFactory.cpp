#include "stdafx.h"
#include "ContextFactory.h"
#include "HoI3Context.h"


ContextFactory::ContextFactory()
{
}


ContextFactory::~ContextFactory()
{
}

void ContextFactory::Init()
{
}

HoI3Context* ContextFactory::CreateDefaultContext() const
{
	QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Paradox Interactive\\Hearts of Iron III", QSettings::NativeFormat);
	HoI3Context *newContext = new HoI3Context(settings.value("path").toString());
	return newContext;
}
