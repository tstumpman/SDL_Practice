#include "Paddle.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"

//Constructor
Paddle::Paddle(
	unsigned char upKeyboardCode,
	unsigned char downKeyboardCode,
	Vector2D screenSize,
	Vector2D size,
	Vector2D position,
	SDL_Color* color,
	float speed
) {
	initialize();
	this->upKeyboardCode = upKeyboardCode;
	this->downKeyboardCode = downKeyboardCode;
	this->speed = speed;
	this->screenSize = screenSize;
	this->size = size;
	this->position = position;
	*(this->color) = *(color);
	this->isAlive = false;
}

void Paddle::initialize() {
	if (color == nullptr) {
		color = new SDL_Color();
	}
	screenSize = Vector2D();
	size = Vector2D();

	isAlive = false;
	currentDirection = DIRECTION::STOP;
	upKeyboardCode = SDL_SCANCODE_W;
	downKeyboardCode = SDL_SCANCODE_S;
	speed = 0.0f;
}

//Copy Assignment operator
Paddle& Paddle::operator=(const Paddle& other) {
	if (this != &other) {
		*(this->color) = *(other.color);
		this->currentDirection = other.currentDirection;
		this->upKeyboardCode = other.upKeyboardCode;
		this->downKeyboardCode = other.downKeyboardCode;
		this->speed = other.speed;
		this->screenSize = other.screenSize;
		this->size = other.size;
		this->position = other.position;
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
Paddle::Paddle(const Paddle& other) {
	initialize();
	*(this->color) = *(other.color);
	this->upKeyboardCode = other.upKeyboardCode;
	this->downKeyboardCode = other.downKeyboardCode;
	this->currentDirection = other.currentDirection;
	this->speed = other.speed;
	this->screenSize = other.screenSize;
	this->size = other.size;
	this->position = other.position;
	this->isAlive = other.isAlive;
}

//Destructor
Paddle::~Paddle() {
	delete this->color;
	this->color = nullptr;
}

void Paddle::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}


void Paddle::processInput() {
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	Paddle::DIRECTION direction = Paddle::DIRECTION::STOP;
	if (keyboardState[upKeyboardCode]) {
		direction = Paddle::DIRECTION::UP;
	}
	if (keyboardState[downKeyboardCode]) {
		direction = Paddle::DIRECTION::DOWN;
	}
	currentDirection = direction;
}

void Paddle::update(float deltaTime) {
	if (!isAlive) return;
	Vector2D yAxis = Vector2D(0, 1);
	position = position + (yAxis * (deltaTime * speed * currentDirection));
	position.clamp(Vector2D(0, 0), screenSize);
}

bool Paddle::getIsAlive() const {
	return this->isAlive;
}

void Paddle::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_Rect renderRect = SDL_Rect{
		int(position.getX() - size.getX() / 2),
		int(position.getY() - size.getY() / 2),
		int(size.getX()),
		int(size.getX())
	};
	SDL_RenderFillRect(renderer, &renderRect);
}