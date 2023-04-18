#ifndef C_TEXT_CHUNK
#define C_TEXT_CHUNK
#include "IGameObject.h"
#include "Vector2D.h"
#include <string>
#define TEXT_CHUNK_FONT_ROWS 8
#define TEXT_CHUNK_FONT_COLUMNS 16
class SDL_Renderer;
struct SDL_Color;
struct SDL_Texture;
class TextChunk : public IGameObject {
public:
	//Default constructor
	TextChunk(
		Vector2D topLeft,
		Vector2D boundarySize,
		Vector2D letterSize,
		SDL_Color* color,
		SDL_Texture* fontTextureSource
	);

	//Copy Assignment operator
	TextChunk& operator=(const TextChunk& other);

	//Copy Constructor
	TextChunk(const TextChunk& other);

	//Destructor
	~TextChunk();

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;
	virtual void setIsAlive(bool isEnabled) override;
	virtual void processInput() override;
	virtual bool getIsAlive() const override;


private: //Functions
	TextChunk();
	void allocateNewData();
	Vector2D convertCharTo2DIndex(char symbol);
	void renderString(std::string string, Vector2D startPosition, Vector2D letterRenderSize, SDL_Renderer* renderer);
protected:
	SDL_Color* color;
	SDL_Texture* fontTextureSource;
	Vector2D boundarySize;
	Vector2D letterSize;
	Vector2D topLeft;
	std::string currentText;
	bool isAlive;

public: //Accessors
	void setPosition(Vector2D updatedPosition);
	void setText(std::string newText);
};

#endif