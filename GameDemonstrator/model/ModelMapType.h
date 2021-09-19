#ifndef MODELMAPTYPE_H
#define MODELMAPTYPE_H

class ModelMapType
{
public:
	/** */
	ModelMapType(const int id);
	/** */
	const int GetId() const;
	/** */
	const QString GetName() const;
private:
	friend class ModelMapTypeCreatorFactoryAbstract;
	const int		Id;
	const QString	Name;
//	QVector<>
};

#endif // MODELMAPTYPE_H