#ifndef GAMEOWNERITEM_H
#define GAMEOWNERITEM_H

class ModelOwnerType;
class GameOwnerItemFactory;

class GameOwnerItem
{
public:
	/** */
	GameOwnerItem(int id);
	/** */
	int GetId() const { return Id; }
	/** */
	QString GetName() const { return Name; }
	/** */
	void SetName(const QString& name) { Name = name; }
	/** */
	bool GetIsHuman() const { return IsHuman; }
	/** */
	int GetModelOwnerTypeId() const { return ModelOwnerTypeId; }
	/** */
	const ModelOwnerType* GetModelOwnerTypeObject() const { return ModelOwnerTypeObject; }
	/** */
	bool operator==(const GameOwnerItem& rhs) const;
	/** */
	QColor GetColor() const;
private:
	friend class GameOwnerItemFactory;
	int			Id;
	QString		Name;
	bool		IsHuman;
	int			ModelOwnerTypeId;
	const ModelOwnerType*	ModelOwnerTypeObject;
};

#endif // GAMEOWNERITEM_H