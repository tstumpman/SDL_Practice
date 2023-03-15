#ifndef C_PADDLE
#define C_PADDLE

class SDL_Renderer;
class SDL_Color;
class SDL_Rect;
class Paddle {
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

	void update(float deltaTime);
	void setBoundary(SDL_Rect* boundary);
	void processInput(DIRECTION direction);
	void render(SDL_Renderer* renderer);
	void setEnabled(bool isEnabled);
	bool getIsAlive();


private: //Functions
	Paddle();
	void initialize();

private:
	SDL_Color* color;
	SDL_Rect* boundary;
	SDL_Rect* paddleShape;
	bool isAlive;
	DIRECTION currentDirection;
	unsigned char upKeyboardCode, downKeyboardCode;
	float speed;
};

#endif