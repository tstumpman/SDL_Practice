#include "Paddle.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"

//Constructor
Paddle::Paddle(
	SDL_Scancode upKeyboardCode,
	SDL_Scancode downKeyboardCode,
	SDL_Rect* boundary,
	SDL_Rect* paddleShape,
	SDL_Color* color,
	float speed
) {
	initialize();
	this->upKeyboardCode = upKeyboardCode;
	this->downKeyboardCode = downKeyboardCode;
	this->speed = speed;
	*(this->color) = *(color);
	*(this->boundary) = *(boundary);
	*(this->paddleShape) = *(paddleShape);
	this->isAlive = false;
}

void Paddle::initialize() {
	if (color == nullptr) {
		color = new SDL_Color();
	}

	if (boundary == nullptr) {
		boundary = new SDL_Rect();
	}

	if (paddleShape == nullptr) {
		paddleShape = new SDL_Rect();
	}

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
		*(this->boundary) = *(other.boundary);
		*(this->paddleShape) = *(other.paddleShape);
		this->currentDirection = other.currentDirection;
		this->upKeyboardCode = other.upKeyboardCode;
		this->downKeyboardCode = other.downKeyboardCode;
		this->speed = other.speed;
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
Paddle::Paddle(const Paddle& other) {
	initialize();
	*(this->color) = *(other.color);
	*(this->boundary) = *(other.boundary);
	*(this->paddleShape) = *(other.paddleShape);
	this->upKeyboardCode = other.upKeyboardCode;
	this->downKeyboardCode = other.downKeyboardCode;
	this->currentDirection = other.currentDirection;
	this->speed = other.speed;
	this->isAlive = other.isAlive;
}

//Destructor
Paddle::~Paddle() {
	delete this->color;
	this->color = nullptr;

	delete this->boundary;
	this->boundary = nullptr;

	delete this->paddleShape;
	this->paddleShape = nullptr;
}

void Paddle::setEnabled(bool isEnabled) {
	this->isAlive = isEnabled;
}

void Paddle::setBoundary(SDL_Rect* boundary) {
	*(this->boundary) = *boundary;
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
	paddleShape->y += speed * currentDirection * deltaTime;
	if (paddleShape->y + paddleShape->h > boundary->h) {
		paddleShape->y = boundary->h - paddleShape->h;
	}
	if (paddleShape->x + paddleShape->x > boundary->w) {
		paddleShape->x = boundary->w - paddleShape->w;
	}
	if (paddleShape->x + 0 < boundary->x) {
		paddleShape->x = boundary->x - 0;
	}
	if (paddleShape->y + 0 < boundary->y) {
		paddleShape->y = boundary->y - 0;
	}
}

bool Paddle::getIsAlive() {
	return this->isAlive;
}

void Paddle::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(renderer, paddleShape);
}