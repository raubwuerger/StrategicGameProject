#ifndef CONFIGFILELOADER_H
#define CONFIGFILELOADER_H

#include <QDomNodeList>

class ConfigFileLoader
{
public:
	/** */
	ConfigFileLoader();
	/** */
	bool LoadConfig(const QString& filename, const QString& rootName);
	/** */
	const QDomNodeList& GetQDomNodeList() const;
private:
	/** */
	bool OpenFile(QFile* file);
	/** */
	bool LoadXMLDocument(QFile& file, const QString& rootName);
private:
	QDomNodeList	DomNodeList;
};

#endif //CONFIGFILELOADER_H
