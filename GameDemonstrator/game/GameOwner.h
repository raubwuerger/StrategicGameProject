#ifndef GAMEOWNER_H
#define GAMEOWNER_H

class ModelOwnerType;
class GameOwnerFactory;

class GameOwner
{
public:
	/** */
	GameOwner(int id);
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
	bool operator==(const GameOwner& rhs) const;
	/** */
	QColor GetColor() const;
private:
	friend class GameOwnerFactory;
	int			Id;
	QString		Name;
	bool		IsHuman;
	int			ModelOwnerTypeId;
	const ModelOwnerType*	ModelOwnerTypeObject;
};

#endif // GAMEOWNER_H