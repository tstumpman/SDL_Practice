#include "TextChunk.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_Rect.h"
#include "Paddle.h"
#include "Projectile.h"

//Constructor
TextChunk::TextChunk(
	Vector2D topLeft,
	Vector2D boundarySize,
	Vector2D letterSize,
	SDL_Color* bodyColor,
	float padding,
	SDL_Color* containerColor,
	float borderWidth,
	SDL_Renderer* renderer,
	SDL_Texture* fontTexture
) {
	this->containerColor = new SDL_Color;
	*(this->containerColor) = *containerColor;
	this->bodyColor = new SDL_Color;
	*(this->bodyColor) = *bodyColor;
	this->fontTextureSource = nullptr;
	this->boundarySize = boundarySize;
	this->letterSize = letterSize;
	this->topLeft = topLeft;
	this->currentText = "";
	this->isAlive = false;
	this->padding = padding;
	this->borderWidth = borderWidth;
	Vector2D borderOffset = Vector2D(borderWidth+padding, borderWidth+padding);
	this->letterSlots = calculateLetterSlots(topLeft + borderOffset, boundarySize - (2 * borderOffset), letterSize);
	this->fontTextureSource = fontTexture;
}

TextChunk::TextChunk() {
	this->containerColor = nullptr;
	this->bodyColor = nullptr;
	this->fontTextureSource = nullptr;
	this->boundarySize = Vector2D();
	this->topLeft = Vector2D();
	this->currentText = "";
	this->letterSize = Vector2D();
	this->isAlive = false;
	this->padding = 0;
	this->borderWidth = 0;
	this->letterSlots = std::vector<SDL_Rect*>();
}

//Destructor
TextChunk::~TextChunk() {
	if (this->containerColor != nullptr) {
		delete containerColor;
		containerColor = nullptr;
	}

	if (this->bodyColor != nullptr) {
		delete bodyColor;
		bodyColor = nullptr;
	}

	for (auto ptr : letterSlots) {
		if (ptr != nullptr) {
			delete ptr;
		}
	}
	letterSlots.clear();
}

void TextChunk::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}


void TextChunk::processInput() {
	//no input
}

void TextChunk::update(float deltaTime) {
	if (!isAlive) return;

}

bool TextChunk::getIsAlive() const {
	return this->isAlive;
}

std::vector<IGameObject*> TextChunk::getChildren() {
	return std::vector<IGameObject*>();
};

IGameObject* TextChunk::getParent() {
	return nullptr;
};

void TextChunk::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	if (currentText.length() == 0) {
		return;
	}

	SDL_Rect containerRect = SDL_Rect{
	int(topLeft.getX()),
	int(topLeft.getY()),
	int(boundarySize.getWidth()),
	int(boundarySize.getHeight())
	};
	SDL_Rect contentRect = SDL_Rect{
	int(containerRect.x + borderWidth),
	int(containerRect.y + borderWidth),
	int(containerRect.w - 2 * borderWidth),
	int(containerRect.h - 2 * borderWidth)
	};

	//Draw a border for the text box
	SDL_SetRenderDrawColor(renderer, containerColor->r, containerColor->g, containerColor->b, containerColor->a);
	//SDL_RenderSetLineWidth(renderer, borderWidth);//TODO: update SDL library to access this function
	SDL_RenderFillRect(renderer, &containerRect);

	//Draw the text box background
	SDL_SetRenderDrawColor(renderer, bodyColor->r, bodyColor->g, bodyColor->b, bodyColor->a);

	SDL_RenderFillRect(renderer, &contentRect);

	//Draw the text
	renderString(currentText, renderer);

	//Present your changes
	//SDL_RenderPresent(renderer);
}

void TextChunk::setPosition(Vector2D updatedPosition) {
	this->topLeft = updatedPosition;
}

void TextChunk::setText(std::string newText) {
	this->currentText = newText;
}

Vector2D TextChunk::convert1DIndexTo2DIndex(int index, int width) {
	int row_index = index / width;
	int col_index = index % width;
	return Vector2D(col_index, row_index);
}

void TextChunk::renderString(std::string string, SDL_Renderer* renderer) {
	
	for (unsigned int index = 0; index < letterSlots.size() && index < string.size(); index++) {
		Vector2D letterSourcePosition = convert1DIndexTo2DIndex(string[index], TEXT_CHUNK_FONT_COLUMNS) * TEXT_CHUNK_LETTER_PIXELS_SOURCE;
		SDL_Rect letterSourceRectangle = SDL_Rect{ int(letterSourcePosition.getX()), int(letterSourcePosition.getY()), TEXT_CHUNK_LETTER_PIXELS_SOURCE, TEXT_CHUNK_LETTER_PIXELS_SOURCE };
		SDL_Rect* targetRect = letterSlots[index];
		SDL_RenderCopy(renderer, fontTextureSource, &letterSourceRectangle, targetRect);
	}
}

std::vector<SDL_Rect*> TextChunk::calculateLetterSlots(
	Vector2D topLeft, 
	Vector2D boundarySize, 
	Vector2D cellSize
) {
	if (cellSize.getWidth() <= 0) return std::vector<SDL_Rect*>();
	if (cellSize.getHeight() <= 0) return std::vector<SDL_Rect*>();
	if (boundarySize.getWidth() <= 0) return std::vector<SDL_Rect*>();
	if (boundarySize.getHeight() <= 0) return std::vector<SDL_Rect*>();

	int columns = boundarySize.getWidth() / cellSize.getWidth();
	int rows = boundarySize.getHeight() / cellSize.getHeight();
	std::vector<SDL_Rect*> returnMe = std::vector<SDL_Rect*>();
	returnMe.resize(rows * columns);

	unsigned int index = 0;
	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < columns; c++) {
			returnMe[index] =
				new SDL_Rect{
					int((c * cellSize.getWidth()) + topLeft.getX()),
					int((r * cellSize.getHeight()) + topLeft.getY()),
					int(letterSize.getWidth()),
					int(letterSize.getHeight())
			};
			index++;
		}
	}
		return returnMe;
}