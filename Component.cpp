#include "Component.h"

void Component::setOwner(std::shared_ptr<GameObject> newOwner)
{
	owner = newOwner;
}
