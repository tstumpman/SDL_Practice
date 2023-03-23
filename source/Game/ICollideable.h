#ifndef I_COLLIDEABLE
#define I_COLLIDEABLE
#include "Vector2D.h"

class ICollideable {
public: 
	virtual ~ICollideable() {};

	virtual bool collidesWith(const ICollideable* other) const = 0;
	virtual void resolveCollision( ICollideable* other) = 0;
	virtual void getCollisionRect( Vector2D& topLeft, Vector2D& size) const = 0;


protected: //Functions
	ICollideable() {};
};

#endif