#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
	: UID(NOT_INITIALIZED_INT)
{

}

void GameObject::SetUID(int uid)
{
	UID = uid;
}

bool GameObject::operator==(const GameObject& rhs) const
{
	return this == &rhs;
}
