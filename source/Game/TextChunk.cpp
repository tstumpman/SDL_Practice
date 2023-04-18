#include "TextChunk.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Paddle.h"
#include "Projectile.h"

//Constructor
TextChunk::TextChunk(
	Vector2D topLeft,
	Vector2D boundarySize,
	Vector2D letterSize,
	SDL_Color* color,
	SDL_Texture* fontTextureSource
) {
	(*this) = TextChunk();
	this->boundarySize = boundarySize;
	this->topLeft = topLeft;
	this->letterSize = letterSize;
	*(this->color) = *(color);
	this->fontTextureSource = fontTextureSource;
	this->isAlive = false;
}

TextChunk::TextChunk() {
	this->color = nullptr;
	this->fontTextureSource = nullptr;
	this->boundarySize = Vector2D();
	this->topLeft = Vector2D();
	this->letterSize = Vector2D();
	this->isAlive = false;
	allocateNewData();
}

void TextChunk::allocateNewData() {
	if (this->color == nullptr) {
		this->color = new SDL_Color();
	}
}

//Copy Assignment operator
TextChunk& TextChunk::operator=(const TextChunk& other) {
	if (this != &other) {
		allocateNewData();
		this->boundarySize = other.boundarySize;
		this->topLeft = other.topLeft;
		this->letterSize = other.letterSize;
		(*this->color) = (*other.color);
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
TextChunk::TextChunk(const TextChunk& other) {
	(*this) = other;
}

//Destructor
TextChunk::~TextChunk() {
	if (this->color != nullptr) {
		delete this->color;
		this->color = nullptr;
	}
}

void TextChunk::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}


void TextChunk::processInput() {
	//Ball is auto controlled.
}

void TextChunk::update(float deltaTime) {
	if (!isAlive) return;

}


bool TextChunk::getIsAlive() const {
	return this->isAlive;
}

void TextChunk::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	if (currentText.length() == 0) {
		return;
	}
	SDL_Rect renderRect = SDL_Rect{
		int(topLeft.getX()),
		int(topLeft.getY()),
		int(boundarySize.getX()),
		int(boundarySize.getY())
	};

	Vector2D targetPos = boundarySize * 0.25f;
	SDL_Rect targetRect = SDL_Rect{int(targetPos.getX()), int(targetPos.getY()), 8, 8};
	
	//Draw the text box background
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(renderer, &renderRect);

	//Draw the text
	renderString(currentText, topLeft, boundarySize * (1.0f / currentText.size()), renderer);

	//Draw a border for the text box
	SDL_SetRenderDrawColor(renderer, 255, 0, 0,255);
	SDL_RenderDrawRect(renderer, &renderRect);
	
	//Present your changes
	SDL_RenderPresent(renderer);
}

void TextChunk::setPosition(Vector2D updatedPosition) {
	this->topLeft = updatedPosition;
}

void TextChunk::setText(std::string newText) {
	this->currentText = newText;
}

Vector2D TextChunk::convertCharTo2DIndex(char symbol) {
	
	int row_index = symbol / TEXT_CHUNK_FONT_COLUMNS;
	int col_index = symbol % TEXT_CHUNK_FONT_COLUMNS;
	return Vector2D(col_index, row_index);
}

void TextChunk::renderString(std::string string, Vector2D startPosition, Vector2D letterRenderSize, SDL_Renderer* renderer) {
	Vector2D currentPosition = startPosition;
	for (unsigned int index = 0; index < string.size(); index++) {
		Vector2D letterSourcePosition = convertCharTo2DIndex(string[index]) * 8;
		SDL_Rect letterSourceRectangle = SDL_Rect{ int(letterSourcePosition.getX()), int(letterSourcePosition.getY()), 8, 8 };
		SDL_Rect targetRect = SDL_Rect{ int(currentPosition.getX()), int(currentPosition.getY()), int(letterRenderSize.getWidth()), int(letterRenderSize.getHeight()) };
		SDL_RenderCopy(renderer, fontTextureSource, &letterSourceRectangle, &targetRect);
		currentPosition = currentPosition + Vector2D(letterRenderSize.getWidth(), 0);
	}
}