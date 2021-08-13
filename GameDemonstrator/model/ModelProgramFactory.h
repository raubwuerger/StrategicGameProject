#ifndef MODELPROGRAMFACTORY_H
#define MODELPROGRAMFACTORY_H

class ModelProgramSettings;

class ModelProgramFactory
{
public:
	/** */
	ModelProgramFactory();
	/** */
	~ModelProgramFactory();
	/** */
	bool Create();
	/** */
	ModelProgramSettings* GetConfig();
public:
	static ModelProgramSettings*	ModelProgramSettingsInstance;
};

#endif // MODELPROGRAMFACTORY_H
