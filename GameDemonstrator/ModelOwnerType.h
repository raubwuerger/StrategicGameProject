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
private:
	friend class OwnerTypeFactory;
	const int Id;
	QString		Name;
	QColor		Color;
	QString		PicturePath;
};
