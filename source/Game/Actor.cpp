#include "Actor.h"
#include "game.h"
#include "Component.h"

Actor::Actor(Game* game) {
	this->game = game;
	this->game->addActor(this);

	this->state = State::Active;
	this->position = Vector2D();
	this->forward = Vector2D();
	this->scale = 1.0f;
	this->rotation = 0.0f;
	this->components = std::vector<Component*>();
}

//Copy Assignment operator
Actor& Actor::operator=(const Actor& other) {
	if (this != &other) {
		this->game = other.game;
		this->state = other.state;
		this->position = other.position;
		this->forward = other.forward;
		this->scale = other.scale;
		this->rotation = other.rotation;
		this->components = std::vector<Component*>();
		for (auto component : other.components) {
			addComponent(component);
		}
	}
	return *this;
}

//Copy Constructor
Actor::Actor(const Actor& other) {
	(*this) = other;
}

Actor::~Actor() {
	for (auto component : components) {
		if (component != nullptr) {
			delete component;
		}
	}
	this->game->removeActor(this);
}

void Actor::update(float deltaTime) {
	updateComponents(deltaTime);
}

void Actor::updateComponents(float deltaTime) {
	for (auto component : components) {
		component->update(deltaTime);
	}
}

void Actor::addComponent(Component* newComponent) {
	int updateOrder = newComponent->getUpdateOrder();
	auto currentComponent = components.begin();
	for (; currentComponent != components.end(); ++currentComponent) {
		if (updateOrder < (*currentComponent)->getUpdateOrder()) {
			break;
		}
	}
	components.insert(currentComponent, newComponent);
}

void Actor::removeComponent(Component* component){
	auto currentComponent = components.begin();
	for (; currentComponent != components.end(); ++currentComponent) {
		if ((*currentComponent) == component) {
			break;
		}
	}
	components.erase(currentComponent);
}

void Actor::processInput(const uint8_t* keyState) {
	if (state != State::Active)
		return;

	for (auto comp : components) {
		comp->processInput(keyState);
	}
	actorInput(keyState);
}

void Actor::setScale(float newScale) {
	this->scale = newScale;
}

Actor::State Actor::getState() const {
	return this->state;
}

Vector2D Actor::getPosition() const {
	return this->position;
}

float Actor::getScale() const {
	return this->scale;
}

void Actor::setRotation(float newRotation) {
	this->rotation = newRotation;
}

float Actor::getRotation() const {
	return this->rotation;
}

void Actor::setForwardVector(Vector2D newVector) {
	this->forward = newVector.getNormal();
}

void Actor::setPosition(Vector2D newPosition) {
	this->position = newPosition;
}

void Actor::setState(Actor::State newState) {
	this->state = newState;
}

Vector2D Actor::getForwardVector() const {
	return this->forward;
}

void Actor::rotateBy(float degrees) {
	this->rotation += degrees;
	while (this->rotation > 360.0) {
		this->rotation -= 360.0f;
	}

	while (this->rotation < 0) {
		this->rotation += 360;
	}
	Vector2D newForwardVector = Vector2D(0, -1).getRotation(this->rotation).getNormal();
	this->setForwardVector(newForwardVector);
}

void Actor::translateBy(Vector2D offset) {
	this->position = position + offset;
}