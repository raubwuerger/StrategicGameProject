#ifndef MODELMAPTYPEINTERFACE_H
#define MODELMAPTYPEINTERFACE_H

class ModelMapTypeInterface
{
public:
	/** */
	ModelMapTypeInterface(int id);
	/** */
	const int GetId() const { return Id; }
private:
	const int Id;
};

#endif // MODELMAPTYPEINTERFACE_H