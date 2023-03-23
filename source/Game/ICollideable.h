#ifndef I_COLLIDEABLE
#define I_COLLIDEABLE
class ICollideable {
public: 
	virtual ~ICollideable() {};

	virtual bool collidesWith(const ICollideable& other) const = 0;
	virtual void resolveCollision(const ICollideable& other) const = 0;


protected: //Functions
	ICollideable() {};
};

#endif