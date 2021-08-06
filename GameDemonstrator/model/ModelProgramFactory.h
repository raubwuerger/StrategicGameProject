#ifndef ModelProgramFactory_H
#define ModelProgramFactory_H

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

#endif
