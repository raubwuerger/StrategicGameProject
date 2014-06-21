#ifndef CONTEXTFACTORY_H
#define CONTEXTFACTORY_H

class HoI3Context;
class ContextFactory
{
public:
/** */
	ContextFactory();
/** */
	~ContextFactory();
/** */
	void Init();
/** */
	HoI3Context* CreateDefaultContext() const;
};

#endif // CONTEXTFACTORY_H