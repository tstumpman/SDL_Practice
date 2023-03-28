#ifndef C_BALL
#define C_BALL
#include "IGameObject.h"
#include "ICollideable.h"
#include "Vector2D.h"
class SDL_Renderer;
class SDL_Color;
class Paddle;
class Ball : public IGameObject, public ICollideable {
public: 
	//Default constructor
	Ball(
		Vector2D boundaryMinimum,
		Vector2D boundaryMaximum,
		Vector2D shape,
		Vector2D position,
		Vector2D velocity,
		SDL_Color* color,
		float maxSpeed
	);

	//Copy Assignment operator
	Ball& operator=(const Ball& other);

	//Copy Constructor
	Ball(const Ball& other);

	//Destructor
	~Ball();

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;
	virtual void setIsAlive(bool isEnabled) override;
	virtual void processInput() override;
	virtual bool getIsAlive() const override;
public://ICollideable overrides
	virtual bool collidesWith(const ICollideable* other) const override;
	virtual void resolveCollision( ICollideable* other) override;
	virtual void getCollisionRect(Vector2D& topLeft, Vector2D& size) const override;
	virtual const Vector2D const getCenter() const override;

private: //Functions
	Ball();
	void allocateNewData();

protected:
	SDL_Color* color;
	Vector2D boundaryMinimum;
	Vector2D boundaryMaximum;
	Vector2D size;
	Vector2D position;
	Vector2D velocity;
	float maxSpeed;
	bool isAlive;

public: //Accessors
	void setPosition(Vector2D updatedPosition);
	void setSpeed(float speed);
	void setDirection(Vector2D direction);
	Vector2D getDirection();
	float getSpeed();
};

#endif