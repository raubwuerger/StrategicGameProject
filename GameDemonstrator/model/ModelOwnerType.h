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
	/* */
	bool GetHuman() const;
	/** */
	QString toString() const;
private:
	friend class ModelOwnerTypeFactory;
	const int Id;
	bool		Human;
	QString		Name;
	QColor		Color;
	QString		PicturePath;
};
