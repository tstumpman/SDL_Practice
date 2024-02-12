#ifndef C_RESTING_BLOCK_BEHAVIOR_H
#define C_RESTING_BLOCK_BEHAVIOR_H
#include "Component.h"

class Actor;
class RestingBlockBehavior : public Component {
public:
	RestingBlockBehavior(Actor* owner, int updateOrder = 10);

	virtual ~RestingBlockBehavior() {};
	void update(float deltaTime) override;

	float getRemainingTimeUntilFreeze() const;
	float getMaxTimeUntilFreeze() const; 
	void setRemainingTimeUntilFreeze(float remainingTime);
	void setMaxTimeUntilFreeze(float maxTime);

protected:
private:

	bool isResting();
	float remainingTimeUntilFreeze;
	float maxTimeUntilFreeze;
};

#endif