#ifndef C_TEXT_CHUNK
#define C_TEXT_CHUNK
#include "IGameObject.h"
#include "Vector2D.h"

#include <string>
#include <vector>
#define TEXT_CHUNK_FONT_ROWS 8
#define TEXT_CHUNK_FONT_COLUMNS 16
#define TEXT_CHUNK_LETTER_PIXELS_SOURCE 16
struct SDL_Color;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;
class TextChunk : public IGameObject {
public:
	//Default constructor
	TextChunk(
		Vector2D topLeft,
		Vector2D boundarySize,
		Vector2D letterSize,
		SDL_Color* backgroundColor,
		float padding,
		SDL_Color* borderColor,
		float borderWidth,
		SDL_Renderer* renderer,
		std::string fontPath
	);

	//Destructor
	~TextChunk();

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;
	virtual void setIsAlive(bool isEnabled) override;
	virtual void processInput() override;
	virtual bool getIsAlive() const override;


private: //Functions
	TextChunk();
	Vector2D convert1DIndexTo2DIndex(int index, int width);
	void renderString(std::string string, SDL_Renderer* renderer);
	std::vector<std::vector<SDL_Rect*>> calculateLetterSlots();
	void releaseTextures();
protected:
	SDL_Color* borderColor;
	float padding;
	SDL_Color* backgroundColor;
	float borderWidth;
	SDL_Texture* fontTextureSource;
	Vector2D boundarySize;
	Vector2D letterSize;
	Vector2D topLeft;
	std::vector<std::vector<SDL_Rect*>> letterSlots;
	std::string currentText;
	std::string fontPath;
	bool isAlive;

public: //Accessors
	void setPosition(Vector2D updatedPosition);
	void setText(std::string newText);
	void setFontPath(std::string newFont, SDL_Renderer * renderer);
};

#endif