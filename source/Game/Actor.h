#ifndef C_ACTOR
#define C_ACTOR

#include <vector>
#include "Vector2D.h"

class Game;
class Component;
class Actor {
public:
	enum State {
		Active,
		Paused,
		Dead,
	};
	Actor(Game* game);

	//Copy Assignment operator
	Actor& operator=(const Actor& other);

	//Copy Constructor
	Actor(const Actor& other);

	virtual ~Actor();
	void update(float deltaTime);
	virtual void updateActor(float deltaTime) = 0;
	void updateComponents(float deltaTime);
	void processInput(const uint8_t* keyState);
	virtual void actorInput(const uint8_t* keystate) {};

	void addComponent(Component* component);
	void removeComponent(Component* component);

	State getState() const;
	float getScale() const;
	float getRotation() const;
	Vector2D getPosition() const;
	Vector2D getForwardVector() const;
	Game* getGame() const;

	void setState(State state);
	void setScale(float newScale);
	void setRotation(float newRotation);
	virtual void setPosition(Vector2D newPosition);
	void setForwardVector(Vector2D newVector);

	void rotateBy(float degrees);
	void translateBy(Vector2D offset);

protected: //Functions

private:
	Game* game;
	State state;
	Vector2D position;
	Vector2D forward;
	float scale;
	float rotation;
	std::vector<Component*> components;
};

#endif