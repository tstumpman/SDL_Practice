#include "Paddle.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"

//Constructor
Paddle::Paddle(
	unsigned char upKeyboardCode,
	unsigned char downKeyboardCode,
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
	color = new SDL_Color();
	boundary = new SDL_Rect();
	paddleShape = new SDL_Rect();
	isAlive = false;
	currentDirection = DIRECTION::STOP;
	upKeyboardCode = 0;
	downKeyboardCode = 0;
	float speed;
}

//Copy Assignment operator
Paddle& Paddle::operator=(const Paddle& other) {
	if (this != &other) {
		*(this->color) = *(other.color);
		*(this->boundary) = *(other.boundary);
		*(this->paddleShape) = *(other.paddleShape);
		this->currentDirection = other.currentDirection;
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
	this->currentDirection = other.currentDirection;
	this->speed = other.speed;
	this->color->r = other.color->r;
	this->color->g = other.color->g;
	this->color->b = other.color->b;
	this->isAlive = other.isAlive;
}

//Destructor
Paddle::~Paddle() {
	delete this->color;
	delete this->boundary;
	delete this->paddleShape;
}

void Paddle::setEnabled(bool isEnabled) {
	this->isAlive = isEnabled;
}

void Paddle::setBoundary(SDL_Rect* boundary) {
	*(this->boundary) = *boundary;
}


void Paddle::processInput(DIRECTION direction) {
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