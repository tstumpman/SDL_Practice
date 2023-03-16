#ifndef C_PADDLE
#define C_PADDLE
#include "IGameObject.h"
class SDL_Renderer;
class SDL_Color;
class SDL_Rect;
class Paddle : public IGameObject {
public: 
	//Default constructor
	Paddle(
		unsigned char upKeyboardCode,
		unsigned char downKeyboardCode,
		SDL_Rect* boundary,
		SDL_Rect* paddleShape,
		SDL_Color* color,
		float speed
	);

	//Copy Assignment operator
	Paddle& operator=(const Paddle& other);

	//Copy Constructor
	Paddle(const Paddle& other);

	//Destructor
	~Paddle();

	enum DIRECTION {
		UP = -1,
		STOP = 0,
		DOWN = 1,
	};

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;
	virtual void setIsAlive(bool isEnabled) override;
	virtual void processInput() override;
	virtual bool getIsAlive() const override;

private: //Functions
	Paddle();
	void initialize();

private:
	SDL_Color* color = nullptr;
	SDL_Rect* boundary = nullptr;
	SDL_Rect* paddleShape = nullptr;
	bool isAlive;
	DIRECTION currentDirection;
	unsigned char upKeyboardCode, downKeyboardCode;
	float speed;
};

#endif