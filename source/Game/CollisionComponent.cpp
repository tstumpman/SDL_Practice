#include "CollisionComponent.h"
#include "Actor.h"
#include "SDL/SDL.h"
#include "../MathUtils.h"

CollisionComponent::CollisionComponent(Actor* owner, CollisionLayer layer) :
	Component(owner)
{
	this->collisionLayer = layer;
	this->size = Vector2D();
}

void CollisionComponent::update(float deltaTime) {

}

void CollisionComponent::handleCollision(CollisionComponent* other) {

}

bool CollisionComponent::collidesWith(CollisionComponent* other) {
	if (owner->getState() != Actor::Active) return false;
	if (this->collisionLayer == CollisionLayer::COLLISION_OFF) return false;
	if (other->collisionLayer == CollisionLayer::COLLISION_OFF) return false;
	if (other->collisionLayer != collisionLayer) return false;

	return other->getRect().getIntersection(getRect()).area() > 0.00001f;
}

void CollisionComponent::setCollisionLayer(CollisionLayer newLayer) {
	this->collisionLayer = newLayer;
}

void CollisionComponent::setSize(Vector2D size) {
	this->size = size;
}

const Rect CollisionComponent::getRect() const {
	return Rect(owner->getPosition(), this->size);
}
