#include "SpriteComponent.h"
#include "Actor.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../MathUtils.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) :
	drawOrder(drawOrder),
	Component(owner)
{
	this->sourceRect = nullptr;
	this->texture = nullptr;
	this->textureHeight = 0;
	this->textureWidth = 0;
	this->drawSize = Vector2D();
}

SpriteComponent::~SpriteComponent() {
	if (this->sourceRect != nullptr) {
		delete sourceRect;
		sourceRect = nullptr;
	}
}
void SpriteComponent::setTexture(SDL_Texture* texture) {
	this->texture = texture;
	SDL_QueryTexture(
		texture, 
		nullptr, 
		nullptr, 
		&this->textureWidth, 
		&this->textureHeight
	);
}

void SpriteComponent::setSourceRect(Rect sourceRect) {
	if (this->sourceRect == nullptr) {
		this->sourceRect = new Rect(sourceRect);
	} else {
		(*this->sourceRect) = sourceRect;
	}
}

void SpriteComponent::setDrawSize(Vector2D size) {
	this->drawSize = size;
}

void SpriteComponent::draw(SDL_Renderer* renderer) {
	if (texture != nullptr) {
		SDL_Rect destinationRect = SDL_Rect();
		destinationRect.w = drawSize.getWidth() * owner->getScale();
		destinationRect.h = drawSize.getHeight() * owner->getScale();
		destinationRect.x = owner->getPosition().getX();
		destinationRect.y = owner->getPosition().getY();

		SDL_Rect temp;
		SDL_Rect* b = nullptr;
		if (sourceRect != nullptr) {
			temp = SDL_Rect{
				(int)sourceRect->getOrigin().getX(),
				(int)sourceRect->getOrigin().getY(),
				(int)sourceRect->getSize().getWidth(),
				(int)sourceRect->getSize().getHeight(),
			};

			b = &temp;
		}
		
		SDL_RenderCopyEx(
			renderer,
			texture,
			b,
			&destinationRect,
			owner->getRotation(),
			nullptr,//point of rotation,
			SDL_FLIP_NONE
		);
	}
}

int SpriteComponent::getDrawOrder() const {
	return this->drawOrder;
}

Vector2D SpriteComponent::getDrawSize() const {
	return drawSize;
}

Vector2D SpriteComponent::getTextureSize() const {
	return Vector2D(textureWidth, textureHeight);
}

SDL_Texture* SpriteComponent::getTexture() const {
	return this->texture;
}

int SpriteComponent::getTextureHeight() const {
	return this->textureHeight;
}
int SpriteComponent::getTextureWidth() const {
	return this->textureWidth;
}