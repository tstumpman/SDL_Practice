#ifndef C_INPUT_COMPONENT_H
#define C_INPUT_COMPONENT_H
#include "MoveComponent.h"

class Actor;
class InputComponent : public MoveComponent {
public:
	InputComponent(Actor* owner, int updateOrder = 10);

	virtual ~InputComponent() {};
	void processInput(const uint8_t* keystate) override;

	float getMaxForwardSpeed() const;
	float getMaxAngularSpeed() const;
	void setMaxForwardSpeed(float speed);
	void setMaxAngularSpeed(float speed);
	void setForwardKey(int key);
	void setBackwardKey(int key);
	void setRotateRightKey(int key);
	void setRotateLeftKey(int key);
	void setLeftKey(int key);
	void setRightKey(int key);

protected:

private:
	float maxForwardSpeed;
	float maxAngularSpeed;
	int forwardKey;
	int backKey;
	int rotateLeftKey;
	int rotateRightKey;
	int leftKey;
	int rightKey;
};

#endif