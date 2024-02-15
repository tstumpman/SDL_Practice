#ifndef C_MONOSPACE_CHARACTER_H
#define C_MONOSPACE_CHARACTER_H
#include<string>
#include "Vector2D.h"
#include "Color.h"
#include "Actor.h"
#include "Rect.h"

class Game;
class SpriteComponent;
class MonospaceCharacter : 
	public Actor {
public: 
	//Default constructor
	MonospaceCharacter(
		Game* game,
		Rect screenRect,
		std::string characterSheet
	);

	//Destructor
	~MonospaceCharacter();

public: //GameObject overrides
	virtual void updateActor(float deltaTime) override;
	virtual void actorInput(const uint8_t* keystate);
	void setCharacter(unsigned char character);

private: //Functions
	MonospaceCharacter();
	Vector2D getTextureCoordinateForCharacter(unsigned char index);

private:
	const int INDEX_WIDTH_OF_2D_ASCII_TABLE = 16;
	const int INDEX_HEIGHT_OF_2D_ASCII_TABLE = 8;
	const Vector2D INDEX_CHARACTER_SCALAR = 
		Vector2D(
			1.0f/ INDEX_WIDTH_OF_2D_ASCII_TABLE, 
			1.0f/ INDEX_HEIGHT_OF_2D_ASCII_TABLE
		);

	SpriteComponent* spriteComponent;

protected:
};

#endif