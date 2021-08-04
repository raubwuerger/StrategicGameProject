#pragma once

class ModelOwnerTypeXMLItems
{
public:
	ModelOwnerTypeXMLItems();
private:
	friend class ModelOwnerTypeFactory;
	const static QString CONFIG_FILE_NAME;
	const static QString ROOT_NAME;
	const static QString ELEMENT_NAME;
	const static QString SUBELEMENT_ID;
	const static QString SUBELEMENT_NAME;
	const static QString SUBELEMENT_PICTURENAME;
	const static QString SUBELEMENT_COLOR;
};