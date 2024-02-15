#ifndef C_TEXT_CHUNK
#define C_TEXT_CHUNK
#include "game.h"
#include "Vector2D.h"
#include "Rect.h"
#include <string>
#include <vector>
class MonospaceCharacter;
class InputComponent;
struct SDL_Color;
struct SDL_Renderer;
struct SDL_Texture;
class TextChunk : public Actor {
public://Functions
	//Default constructor
	TextChunk(
		Game* game,
		Vector2D boundarySize,
		unsigned char lettersPerRow,
		unsigned char rows,
		std::string font
	);

	//Destructor
	~TextChunk();

	virtual void updateActor(float deltaTime);
	virtual void actorInput(const uint8_t* keystate) override;
	std::string setText(std::string newText);
	void clearText();
	void setPosition(Vector2D newPos) override;
	void setBackgroundColor(SDL_Color color);

	Rect getBoundary() const;

private://functions
	TextChunk();
	Vector2D convert1DIndexTo2DIndex(int index, int width);
	std::vector<Rect> calculateLetterSlots(Rect boundary, unsigned int cols, unsigned int rows);
protected://functions
public: //Data
private://Data
	Vector2D boundarySize;
	SDL_Color* backgroundColor;
	unsigned char columns;
	unsigned char rows;
	std::string currentText;
	InputComponent* inputComponent;
	std::vector<Rect> letterSlots;
	std::vector<MonospaceCharacter*> characters;

protected://Data
};

#endif