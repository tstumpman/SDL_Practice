#include "TextChunk.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_Rect.h"
#include "Paddle.h"
#include "Projectile.h"

//Constructor
TextChunk::TextChunk(
	Vector2D topLeft,
	Vector2D boundarySize,
	Vector2D letterSize,
	SDL_Color* backgroundColor,
	float padding,
	SDL_Color* borderColor,
	float borderWidth,
	SDL_Renderer* renderer,
	std::string fontPath
) {
	this->borderColor = new SDL_Color;
	*(this->borderColor) = *borderColor;
	this->backgroundColor = new SDL_Color;
	*(this->backgroundColor) = *backgroundColor;
	this->fontTextureSource = nullptr;
	this->boundarySize = boundarySize;
	this->letterSize = letterSize;
	this->topLeft = topLeft;
	this->currentText = "";
	this->isAlive = false;
	this->padding = padding;
	this->borderWidth = borderWidth;
	this->letterSlots = calculateLetterSlots();
	setFontPath(fontPath, renderer);
}

TextChunk::TextChunk() {
	this->borderColor = nullptr;
	this->backgroundColor = nullptr;
	this->fontTextureSource = nullptr;
	this->boundarySize = Vector2D();
	this->topLeft = Vector2D();
	this->currentText = "";
	this->letterSize = Vector2D();
	this->isAlive = false;
	this->padding = 0;
	this->borderWidth = 0;
	this->letterSlots = calculateLetterSlots();
}

void TextChunk::releaseTextures() {
	if (this->fontTextureSource != nullptr) {
		SDL_DestroyTexture(fontTextureSource);
		fontTextureSource = nullptr;
	}
}
//Destructor
TextChunk::~TextChunk() {
	if (this->borderColor != nullptr) {
		delete borderColor;
		borderColor = nullptr;
	}

	if (this->backgroundColor != nullptr) {
		delete backgroundColor;
		borderColor = nullptr;
	}

	releaseTextures();

	for (auto& rowVec : letterSlots) {
		for (auto ptr : rowVec) {
			if (ptr != nullptr) {
				delete ptr;
			}
		}
		rowVec.clear();
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

void TextChunk::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	if (currentText.length() == 0) {
		return;
	}

	SDL_Rect borderRect = SDL_Rect{
	int(topLeft.getX()),
	int(topLeft.getY()),
	int(boundarySize.getWidth()),
	int(boundarySize.getHeight())
	};
	SDL_Rect paddingRect = SDL_Rect{
	int(borderRect.x + borderWidth),
	int(borderRect.y + borderWidth),
	int(borderRect.w - 2*borderWidth),
	int(borderRect.h - 2*borderWidth)
	};

	//Draw a border for the text box
	SDL_SetRenderDrawColor(renderer, 255, 0, 0,255);
	SDL_RenderFillRect(renderer, &borderRect);

	//Draw the text box background
	SDL_SetRenderDrawColor(renderer, 128, 128, 255, 255);
	SDL_RenderFillRect(renderer, &paddingRect);

	//Draw the text
	renderString(currentText, renderer);

	
	//Present your changes
	SDL_RenderPresent(renderer);
}

void TextChunk::setPosition(Vector2D updatedPosition) {
	this->topLeft = updatedPosition;
}

void TextChunk::setText(std::string newText) {
	this->currentText = newText;
}

void TextChunk::setFontPath(std::string newFontPath, SDL_Renderer * renderer) {
	releaseTextures();
	this->fontTextureSource = IMG_LoadTexture(renderer, newFontPath.c_str());
}

Vector2D TextChunk::convert1DIndexTo2DIndex(int index, int width) {
	int row_index = index / width;
	int col_index = index % width;
	return Vector2D(col_index, row_index);
}

void TextChunk::renderString(std::string string, SDL_Renderer* renderer) {
	for (unsigned int index = 0; index < string.size(); index++) {
		Vector2D letterSourcePosition = convert1DIndexTo2DIndex(string[index], TEXT_CHUNK_FONT_COLUMNS) * TEX;
		SDL_Rect letterSourceRectangle = SDL_Rect{ int(letterSourcePosition.getX()), int(letterSourcePosition.getY()), 8, 8 };
		Vector2D targetIndex = convert1DIndexTo2DIndex(index, letterSlots[0].size());
		SDL_Rect* targetRect = letterSlots[targetIndex.getHeight()][targetIndex.getWidth()];
		SDL_RenderCopy(renderer, fontTextureSource, &letterSourceRectangle, targetRect);
	}
}

std::vector<std::vector<SDL_Rect*>> TextChunk::calculateLetterSlots() {
	if (letterSize.getWidth() == 0) return std::vector<std::vector<SDL_Rect*>>();
	if (letterSize.getHeight() == 0) return std::vector<std::vector<SDL_Rect*>>();

	Vector2D letterArea = Vector2D(boundarySize.getWidth() - 2*(borderWidth + padding), boundarySize.getHeight() - 2*(borderWidth + padding));
	int columns = letterArea.getWidth() / letterSize.getWidth();
	int rows = letterArea.getHeight()/ letterSize.getHeight();
	std::vector<std::vector<SDL_Rect*>> returnMe = std::vector<std::vector<SDL_Rect*>>();
	returnMe.resize(rows);
	
	for (unsigned int r = 0; r < returnMe.size(); r++) {
		returnMe[r].resize(columns);
		for (unsigned int c = 0; c < returnMe[r].size(); c++) {
			returnMe[r][c] =
				new SDL_Rect{
					int((c * letterSize.getWidth()) + (padding + borderWidth)),
					int((r * letterSize.getHeight()) + (padding + borderWidth)),
					int(letterSize.getWidth()),
					int(letterSize.getHeight())
			};
		}
	}
	return returnMe;
}