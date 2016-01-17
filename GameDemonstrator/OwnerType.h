#pragma once

namespace GDModel
{

class COwnerType
{
public:
	/** */
	COwnerType( int id );
	/** */
	~COwnerType();
	/** */
	int GetId() const;
	/** Get Name */	
	const QString& GetName() const;
private:
	friend class COwnerTypeFactory;
	const int Id;
	QString		Name;
	QColor		Color;
	QString		PicturePath;
};

}