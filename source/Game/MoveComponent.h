#ifndef C_MOVE_COMPONENT
#define C_MOVE_COMPONENT
#include "Component.h"

class Actor;
class MoveComponent : public Component {
public:
	MoveComponent(Actor* owner, int updateOrder = 10);

	virtual ~MoveComponent() {};
	void update(float deltaTime) override;

	float getAngularSpeed() const;
	float getForwardSpeed() const; 
	float getHorizontalSpeed() const; 
	void setAngularSpeed(float speed);
	void setForwardSpeed(float speed);
	void setHorizontalSpeed(float speed);

protected:
private:
	float angularSpeed;
	float forwardSpeed;
	float horizontalSpeed;
};

#endif