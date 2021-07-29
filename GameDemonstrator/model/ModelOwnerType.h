#pragma once

class ModelOwnerType
{
public:
	/** */
	ModelOwnerType( int id );
	/** */
	~ModelOwnerType();
	/** */
	int GetId() const;
	/** Get Name */	
	const QString& GetName() const;
	/** */
	QString toString() const;
private:
	friend class ModelOwnerTypeFactory;
	const int Id;
	QString		Name;
	QColor		Color;
	QString		PicturePath;
};
