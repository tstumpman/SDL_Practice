#ifndef SINE_WAVE_OBJECT
#define SINE_WAVE_OBJECT
#include "IGameObject.h"

class SDL_Renderer;
class SDL_Color;
class SDL_Rect;

class SineWaveObject : public IGameObject {
public:
	//Default constructor
	SineWaveObject(
		float anchor,
		float speed,
		float amplitude,
		float frequency,
		SDL_Rect* shape,
		SDL_Rect* boundary,
		SDL_Color* color
	);

	//Copy Assignment operator
	SineWaveObject& operator=(const SineWaveObject& other);

	//Copy Constructor
	SineWaveObject(const SineWaveObject& other);

	//Destructor
	~SineWaveObject();

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;
	virtual void setIsAlive(bool isEnabled) override;
	virtual void processInput() override {};
	virtual bool getIsAlive() const override;

	void initialize(
		float anchor,
		float speed,
		float amplitude,
		float frequency,
		SDL_Rect* shape,
		SDL_Rect* boundary,
		SDL_Color* color
	);

private: //Functions
	SineWaveObject();

private:
	SDL_Color* color;
	SDL_Rect* shape;
	SDL_Rect* boundary;
	float anchor;
	float speed;
	float rotation;
	float frequency;
	float amplitude;
	bool isAlive;
};

#endif