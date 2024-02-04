#include "TextChunk.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_Rect.h"
#include "MoveComponent.h"
#include "Paddle.h"
#include "MonospaceCharacter.h"
#include "InputComponent.h"
#include "Projectile.h"

//Constructor
TextChunk::TextChunk(
	Game* game,
	Vector2D boundarySize,
	unsigned char lettersPerRow,
	unsigned char rows,
	std::string font,
	SDL_Color* backgroundColor
) :
	Actor(game)
{
	this->backgroundColor = new SDL_Color;
	*(this->backgroundColor) = *backgroundColor;
	this->inputComponent = new InputComponent(this);
	inputComponent->setForwardKey(SDL_SCANCODE_T);
	inputComponent->setBackwardKey(SDL_SCANCODE_G);
	inputComponent->setRotateLeftKey(SDL_SCANCODE_F);
	inputComponent->setRotateRightKey(SDL_SCANCODE_H);
	this->inputComponent->setMaxForwardSpeed(game->getWindowSize().getHeight() / 5.0f);
	this->inputComponent->setMaxAngularSpeed(360.0f);


	this->currentText = "";
	this->columns = lettersPerRow;
	this->rows = rows;
	this->boundarySize = boundarySize;
	this->letterSlots = calculateLetterSlots(getBoundary(), columns, rows);
	characters = std::vector<MonospaceCharacter*>();
	for (Rect &slot : letterSlots) {
		characters.push_back(new MonospaceCharacter(game, slot, font));
	}
}

//Destructor
TextChunk::~TextChunk() {
	for (auto character : characters) {
		character->setState(Actor::State::Dead);
	}
	if (this->backgroundColor != nullptr) {
		delete backgroundColor;
		backgroundColor = nullptr;
	}
}

void TextChunk::actorInput(const uint8_t* keystate) {
	this->inputComponent->processInput(keystate);
}

Rect TextChunk::getBoundary() const {
	return Rect(
		getPosition(),
		boundarySize
	);
}

void TextChunk::updateActor(float deltaTime) {

}

std::string TextChunk::setText(std::string newText) {
	clearText();

	unsigned int numCharactersToModify = std::min(rows * columns, (int)newText.size());
	std::string workingString = newText.substr(0, numCharactersToModify);
	for (unsigned int i = 0; i < numCharactersToModify; i++) {
		characters[i]->setCharacter(workingString[i]);
	}
	newText.erase(0, numCharactersToModify);
	return newText;
}

void TextChunk::clearText() {
	for (unsigned int i = 0; i < characters.size(); i++) {
		characters[i]->setCharacter(' ');
	}
}

void TextChunk::setPosition(Vector2D newPosition) {
	Actor::setPosition(newPosition);
	this->letterSlots = calculateLetterSlots(getBoundary(), columns, rows);
	for (unsigned int i = 0; i < rows * columns; i++) {
		characters[i]->setPosition(letterSlots[i].getOrigin());
	}
}

Vector2D TextChunk::convert1DIndexTo2DIndex(int index, int width) {
	int row_index = index / width;
	int col_index = index % width;
	return Vector2D(col_index, row_index);
}

std::vector<Rect> TextChunk::calculateLetterSlots(
	Rect boundary,
	unsigned int cols,
	unsigned int rows
) {
	float cellWidth = boundary.getSize().getWidth() / (float)cols;
	float cellHeight = boundary.getSize().getHeight() / (float)rows;
	std::vector<Rect> returnMe = std::vector<Rect>();
	returnMe.resize(rows * cols);

	unsigned int index = 0;
	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			returnMe[index] =
				Rect(
					int((c * cellWidth) + boundary.getOrigin().getX()),
					int((r * cellHeight) + boundary.getOrigin().getY()),
					int(cellWidth),
					int(cellHeight)
				);
			index++;
		}
	}
	return returnMe;
}