#include "component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder) {
	this->owner = owner;
	this->updateOrder = updateOrder;
}

int Component::getUpdateOrder() const {
	return this->updateOrder;
}