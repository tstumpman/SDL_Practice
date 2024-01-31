#include "SineWaveObject.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"

//Constructor
SineWaveObject::SineWaveObject(
	float anchor,
	float speed,
	float amplitude,
	float frequency,
	SDL_Rect* shape,
	SDL_Rect* boundary,
	SDL_Color* color
)
{
	initialize(
		anchor,
		speed,
		amplitude,
		frequency,
		shape,
		boundary,
		color
	);
}

//Copy Assignment operator
SineWaveObject& SineWaveObject::operator=(const SineWaveObject& other) {
	if (this != &other) {
	initialize(
		other.anchor,
		other.speed,
		other.amplitude,
		other.frequency,
		other.shape,
		other.boundary,
		other.color
	);
	this->isAlive = other.isAlive;
	this->rotation = other.rotation;
	}
	return *this;
}

//Copy Constructor
SineWaveObject::SineWaveObject(const SineWaveObject& other) {
	initialize(
		other.anchor,
		other.speed,
		other.amplitude,
		other.frequency,
		other.shape,
		other.boundary,
		other.color
	);
	this->isAlive = other.isAlive;
	this->rotation = other.rotation;
}


//Destructor
SineWaveObject::~SineWaveObject() {
	if (this->color != nullptr) {
		delete this->color;
		this->color = nullptr;
	}
	if (this->shape != nullptr) {
		delete this->shape;
		this->shape = nullptr;
	}
	if (this->boundary != nullptr) {
		delete this->boundary;
		this->boundary = nullptr;
	}
}

void SineWaveObject::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}

void SineWaveObject::initialize(
	float anchor,
	float speed,
	float amplitude,
	float frequency,
	SDL_Rect* shape,
	SDL_Rect* boundary,
	SDL_Color* color
) {
	if (this->shape == nullptr) {
		this->shape = new SDL_Rect();
	}

	if (this->boundary == nullptr) {
		this->boundary = new SDL_Rect();
	}

	if (this->color == nullptr) {
		this->color = new SDL_Color();
	}
	*(this->shape) = *shape;
	*(this->boundary) = *boundary;
	*(this->color) = *color;

	this->amplitude = amplitude;
	this->frequency = frequency;
	this->speed = speed;
	this->anchor = anchor;

	this->rotation = 0.0f;
	this->setIsAlive(true);
}

void SineWaveObject::update(float deltaTime) {

	if (isAlive) {
		shape->x += speed * deltaTime;

		if (speed > 1) {
			if (shape->x + 0 > boundary->w) {
				speed = speed * -1.0f;
			}
		}
		else if (speed < -1) {
			if (shape->x + shape->w < boundary->x) {
				speed = speed * -1.0f;
			}
		}
		else {
			shape->x = 0;
			shape->y = 0;
			anchor = boundary->h / 2;
			speed = 10;
		}

		rotation += deltaTime * frequency * Math::RADIANS_PER_CIRCLE;
		while (rotation > Math::RADIANS_PER_CIRCLE) {
			rotation -= Math::RADIANS_PER_CIRCLE;
		}
		float currentPhase = cos(rotation);
		shape->y = amplitude * currentPhase + anchor - shape->h / 2;
	}
}

bool SineWaveObject::getIsAlive() const {
	return this->isAlive;
}
std::vector<IGameObject*> SineWaveObject::getChildren() {
	return std::vector<IGameObject*>();
};

IGameObject* SineWaveObject::getParent() {
	return nullptr;
};
void SineWaveObject::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(renderer, shape);
}