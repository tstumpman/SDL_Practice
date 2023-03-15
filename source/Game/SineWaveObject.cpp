#include "SineWaveObject.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"

//Constructor
SineWaveObject::SineWaveObject() {
	this->objPosX = 0;
	this->objPosY = 0;
	this->anchor = 0;
	this->height = 0;
	this->width = 0;
	this->amplitude = 0;
	this->frequency = 0;
	this->speed = 0;
	this->color = new SDL_Color{ 255,255, 255, 255 };
	this->rotation = 0.0f;
	this->isAlive = false;
}

//Copy Assignment operator
SineWaveObject& SineWaveObject::operator=(const SineWaveObject& other) {
	if (this != &other) {
		this->objPosX = other.objPosX;
		this->objPosY = other.objPosY;
		this->anchor = other.anchor;
		this->height = other.height;
		this->width = other.width;
		this->amplitude = other.amplitude;
		this->frequency = other.frequency;
		this->speed = other.speed;
		this->color->r = other.color->r;
		this->color->g = other.color->g;
		this->color->b = other.color->b;
		this->rotation = other.rotation;
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
SineWaveObject::SineWaveObject(const SineWaveObject& other) {
	color = new SDL_Color();
	this->objPosX = other.objPosX;
	this->objPosY = other.objPosY;
	this->anchor = other.anchor;
	this->height = other.height;
	this->width = other.width;
	this->amplitude = other.amplitude;
	this->frequency = other.frequency;
	this->speed = other.speed;
	this->color->r = other.color->r;
	this->color->g = other.color->g;
	this->color->b = other.color->b;
	this->rotation = other.rotation;
	this->isAlive = other.isAlive;
}

//Destructor
SineWaveObject::~SineWaveObject() {
	delete this->color;
}

void SineWaveObject::setEnabled(bool isEnabled) {
	this->isAlive = isEnabled;
}

void SineWaveObject::resetAll(
	float anchor,
	float speed,
	float height,
	float width,
	float amplitude,
	float frequency,
	SDL_Color* color
) {
	if (speed < 0) {
		speed *= -1;
	}
	this->objPosX = 0-width/2;
	this->objPosY = anchor - height/2;
	this->anchor = anchor;
	this->height = height;
	this->width = width;
	this->amplitude = amplitude;
	this->frequency = frequency;
	this->speed = speed;
	this->color->r = color->r;
	this->color->g = color->g;
	this->color->b = color->b;
	this->rotation = 0.0f;
	this->setEnabled(true);
}

void SineWaveObject::update(float deltaTime, float screenWidth, float screenHeight) {

	if (isAlive) {
		objPosX += speed * deltaTime;
		if (objPosX - width/2 > screenWidth) {
			isAlive = false;
		}

		rotation += deltaTime * frequency * RADIANS_PER_CIRCLE;
		while (rotation > RADIANS_PER_CIRCLE) {
			rotation -= RADIANS_PER_CIRCLE;
		}
		float currentPhase = cos(rotation);
		objPosY = amplitude * currentPhase + anchor;
	}
}

bool SineWaveObject::getIsAlive() {
	return this->isAlive;
}

void SineWaveObject::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	float alpha = 255;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_Rect paddleRect = SDL_Rect();
	paddleRect.h = height;
	paddleRect.w = width;
	paddleRect.x = objPosX - paddleRect.w / 2.0f;
	paddleRect.y = objPosY - paddleRect.h / 2.0f;
	SDL_RenderFillRect(renderer, &paddleRect);
}