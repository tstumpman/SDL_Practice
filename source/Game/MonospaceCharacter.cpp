#include "MonospaceCharacter.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SpriteComponent.h"
#include "game.h"


//Constructor
MonospaceCharacter::MonospaceCharacter(
	Game* game,
	Rect screenRect,
	std::string characterSheet
) : Actor(game) {
	this->setForwardVector(Vector2D(0, -1).getNormal());
	this->setPosition(screenRect.getOrigin());
	this->spriteComponent = new SpriteComponent(this);
	spriteComponent->setTexture(game->getTexture(characterSheet));
	spriteComponent->setDrawSize(screenRect.getSize());

	getGame()->addSprite(spriteComponent);
}

//Destructor
MonospaceCharacter::~MonospaceCharacter() {
	removeComponent(spriteComponent);
	delete spriteComponent;
}

void MonospaceCharacter::actorInput(const uint8_t * keyboardState) {
}

void MonospaceCharacter::updateActor(float deltaTime) {
}

Vector2D MonospaceCharacter::getTextureCoordinateForCharacter(unsigned char character){
	int row_index = (character / INDEX_WIDTH_OF_2D_ASCII_TABLE);
	int col_index = (character % INDEX_WIDTH_OF_2D_ASCII_TABLE);
	return Vector2D(col_index, row_index);
}

void MonospaceCharacter::setCharacter(unsigned char character) {
	Vector2D characterSheetDimensions = spriteComponent->getTextureSize();
	Vector2D sourceCharacterSize = characterSheetDimensions * INDEX_CHARACTER_SCALAR;
	Vector2D textureIndexCoordinate = getTextureCoordinateForCharacter(character);
	Vector2D sourceCharacterPos = textureIndexCoordinate * sourceCharacterSize;
	Rect sourceRect = Rect(sourceCharacterPos, sourceCharacterSize);
	spriteComponent->setSourceRect(sourceRect);
}