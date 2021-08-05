#ifndef MODELUNIT_H
#define MODELUNIT_H

class ModelUnitType
{
public:
	/** */
	ModelUnitType(int id);
	/** */
	int GetId() const;
	/** */
	const QImage* GetImage() const;
	/** */
	const QString& GetName() const;
	/** */
	const QString& GetPicturePath() const;
	/** */
	void SetImage(const QImage* image);
private:
	friend class ModelUnitTypeFactory;
	const int		Id;
	QString			Name;
	QString			PicturePath;
	const QImage	*Image;
};

#endif