#include "SineWaveObject.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"

SineWaveObject::SineWaveObject() {
	this->objPosX = 0;
	this->objPosY = 0;
	this->anchor = 0;
	this->height = 0;
	this->width = 0;
	this->amplitude = 0;
	this->frequency = 0;
	this->lifetime = 0;
	this->speed = 0;
	this->colorR = 0;
	this->colorG = 0;
	this->colorB = 0;
	this->rotation = 0.0f;
	this->elapsedTime = 0.0f;
	this->isAlive = false;
}

void SineWaveObject::setEnabled(bool isEnabled) {
	this->isAlive = isEnabled;
}

void SineWaveObject::resetAll(
	float startXPos,
	float startYPos,
	float anchor,
	float speed,
	float height,
	float width,
	float amplitude,
	float frequency,
	float lifetime,
	uint8_t colorR,
	uint8_t colorG,
	uint8_t colorB
) {
	this->objPosX = startXPos;
	this->objPosY = startYPos;
	this->anchor = anchor;
	this->height = height;
	this->width = width;
	this->amplitude = amplitude;
	this->frequency = frequency;
	this->lifetime = lifetime;
	this->speed = speed;
	this->colorR = colorR;
	this->colorG = colorG;
	this->colorB = colorB;
	this->rotation = 0.0f;
	this->elapsedTime = 0.0f;
	this->setEnabled(true);
}

void SineWaveObject::update(float deltaTime, float screenWidth, float screenHeight) {
	elapsedTime += deltaTime;
	if (elapsedTime > lifetime) {
		isAlive = false;
	}
	if (isAlive) {

		objPosX += speed * deltaTime;
		while (objPosX > screenWidth) {
			objPosX -= screenWidth;
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
	float remainingLife = (lifetime - elapsedTime)/lifetime;
	float alpha = remainingLife * 255;
	SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, alpha);
	SDL_Rect paddleRect = SDL_Rect();
	paddleRect.h = height;
	paddleRect.w = width;
	paddleRect.x = objPosX - paddleRect.w / 2.0f;
	paddleRect.y = objPosY - paddleRect.h / 2.0f;
	SDL_RenderFillRect(renderer, &paddleRect);
}