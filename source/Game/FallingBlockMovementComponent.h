#ifndef C_FALLING_BLOCK_MOVEMENT_COMPONENT_H
#define C_FALLING_BLOCK_MOVEMENT_COMPONENT_H
#include "Component.h"

class Actor;
class FallingBlockMovementComponent : public Component {
public:
	FallingBlockMovementComponent(Actor* owner, int updateOrder = 10);

	virtual ~FallingBlockMovementComponent() {};
	void update(float deltaTime) override;

	float getFallingSpeed() const;
	float getTimeUntilNextFall() const; 
	float getFallingInterval() const; 
	void setFallingSpeed(float unitsPerMovement);
	void setTimeUntilNextFall(float remainingTime);
	void setFallingInterval(float timeBetweenMovements);

protected:
private:
	float fallingSpeed;
	float timeUntilNextFall;
	float fallingInterval;
};

#endif