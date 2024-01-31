#ifndef C_COMPONENT
#define C_COMPONENT
#include <stdint.h>

class Actor;
class Component {
public:
	Component(Actor* owner, int updateOrder = 100);

	virtual ~Component() {};
	virtual void update(float deltaTime) = 0;
	int getUpdateOrder() const;
	virtual void processInput(const uint8_t* keystate) {}

protected:
	Actor* owner;
	int updateOrder;

	void safeDelete(void* pointer) {
		if (pointer != nullptr) {
			pointer = nullptr;
		}
	}

private:
};

#endif