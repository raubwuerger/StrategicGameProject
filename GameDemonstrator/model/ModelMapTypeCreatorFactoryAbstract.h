#ifndef MODELMAPTYPECREATORFACTORYABSTRACT_H
#define MODELMAPTYPECREATORFACTORYABSTRACT_H

class ModelMapType;
class QDomNode;

class ModelMapTypeCreatorFactoryAbstract
{
public:
	/** */
	bool Create();
private:
	/** */
	ModelMapType* CreateFromXML(const QDomNode& node);

};

#endif // MODELMAPTYPECREATORFACTORYABSTRACT_H