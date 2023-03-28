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
	Vector2D normal,
	SDL_Color* color,
	float speed
) {
	(*this) = Paddle();
	this->upKeyboardCode = upKeyboardCode;
	this->downKeyboardCode = downKeyboardCode;
	this->speed = speed;
	this->screenSize = screenSize;
	this->normal = normal;
	this->size = size;
	this->position = position;
	*(this->color) = *(color);
	this->isAlive = false;
	
	if (projectile != nullptr) {
		delete projectile;
		projectile == nullptr;
	}
	this->projectile = new Projectile(
		Vector2D(0, 0),
		Vector2D(screenSize.getWidth(), screenSize.getHeight()),
		size * 0.25f,
		position + normal * (size * 0.25f).getWidth(),
		this->normal,
		this->color,
		speed
	);
}

void Paddle::allocateNewData() {
	if (this->color == nullptr) {
		this->color = new SDL_Color();
	}
	if (this->projectile == nullptr) {
		SDL_Color white = SDL_Color{ 0, 0 , 0, 0 };
		projectile = new Projectile(
			Vector2D(),
			Vector2D(),
			Vector2D(),
			Vector2D(),
			Vector2D(),
			&white,
			0.0f);
	}
}
Paddle::Paddle() {
	color = nullptr;
	projectile = nullptr;

	screenSize = Vector2D();
	size = Vector2D();
	position = Vector2D();
	normal = Vector2D(1,0);

	isAlive = false;
	currentDirection = DIRECTION::STOP;
	upKeyboardCode = SDL_SCANCODE_W;
	downKeyboardCode = SDL_SCANCODE_S;
	speed = 0.0f;

	allocateNewData();
}

//Copy Assignment operator
Paddle& Paddle::operator=(const Paddle& other) {
	if (this != &other) {
		allocateNewData();
		*(this->color) = *(other.color);
		*(this->projectile) = *(other.projectile);
		this->currentDirection = other.currentDirection;
		this->upKeyboardCode = other.upKeyboardCode;
		this->downKeyboardCode = other.downKeyboardCode;
		this->speed = other.speed;
		this->screenSize = other.screenSize;
		this->size = other.size;
		this->position = other.position;
		this->normal = other.normal;
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
Paddle::Paddle(const Paddle& other) {
	(*this) = other;
}

//Destructor
Paddle::~Paddle() {
	if (this->color != nullptr) {
		delete this->color;
		this->color = nullptr;
	}

	if (this->projectile != nullptr) {
		delete this->projectile;
		this->projectile = nullptr;
	}
}

void Paddle::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}


void Paddle::processInput() {
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	Paddle::DIRECTION direction = Paddle::DIRECTION::STOP;
	bool upPressed = keyboardState[upKeyboardCode];
	bool downPressed = keyboardState[downKeyboardCode];
	if (upPressed) {
		direction = Paddle::DIRECTION::UP;
	}

	if (keyboardState[downKeyboardCode]) {
		direction = Paddle::DIRECTION::DOWN;
	}

	if (upPressed && downPressed) {
		projectile->launch(position);
	}

	currentDirection = direction;
}

bool Paddle::collidesWith(const ICollideable* other) const {
	Vector2D otherTopLeft;
	Vector2D otherSize;
	other->getCollisionRect(otherTopLeft, otherSize);
	// Check if the rectangles intersect in the X-axis
	bool xOverlap = ((position.getX() - size.getWidth() / 2) < (otherTopLeft.getX() + otherSize.getWidth())) && ((position.getX() + size.getWidth() / 2) > otherTopLeft.getX());

	// Check if the rectangles intersect in the Y-axis
	bool yOverlap = ((position.getY() - size.getHeight() / 2) < (otherTopLeft.getY() + otherSize.getHeight())) && ((position.getY() + size.getHeight() / 2) > otherTopLeft.getY());

	// Return true if both X-axis and Y-axis overlaps
	return xOverlap && yOverlap;

}

void Paddle::resolveCollision( ICollideable* other) {
	//Paddle can collide with a ball and a bullet, but it only cares if it collides with a bullet.
}

void Paddle::getCollisionRect(Vector2D& topLeft, Vector2D& size) const {
	topLeft = (this->position - (this->size * 0.5f));
	size = this->size;
}

void Paddle::update(float deltaTime) {
	if (!isAlive) return;
	Vector2D yAxis = Vector2D(0, 1);
	position = position + (yAxis * (deltaTime * speed * currentDirection));
	position.clamp(Vector2D(0, 0), screenSize);
	projectile->update(deltaTime);
}

bool Paddle::getIsAlive() const {
	return this->isAlive;
}

void Paddle::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_Rect renderRect = SDL_Rect{
		int(position.getX() - size.getWidth() / 2.0f),
		int(position.getY() - size.getHeight() / 2.0f),
		int(size.getX()),
		int(size.getY())
	};
	SDL_RenderFillRect(renderer, &renderRect);
	projectile->render(renderer);
}

Vector2D Paddle::getNormal() {
	return normal;
}

const Vector2D const Paddle::getCenter() const {
	return this->position;
}

 Projectile* Paddle::getBullet() {
	return this->projectile;
}
