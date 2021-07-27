#pragma once

class OwnerType
{
public:
	/** */
	OwnerType( int id );
	/** */
	~OwnerType();
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
