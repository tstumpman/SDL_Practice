#ifndef SINE_WAVE_OBJECT
#define SINE_WAVE_OBJECT

class SDL_Renderer;
class SDL_Color;
class SineWaveObject {
public: 
	//Default constructor
	SineWaveObject();

	//Copy Assignment operator
	SineWaveObject& operator=(const SineWaveObject& other);

	//Copy Constructor
	SineWaveObject(const SineWaveObject & other);

	//Destructor
	~SineWaveObject();

	void update(float deltaTime, float screenWidth, float screenHeight);
	void render(SDL_Renderer* renderer);
	void setEnabled(bool isEnabled);
	void resetAll(
		float anchor,
		float speed,
		float height,
		float width,
		float amplitude,
		float frequency,
		SDL_Color* color
	);
	bool getIsAlive();
private: //Functions
private:
	SDL_Color* color;
	float objPosX;
	float objPosY;
	float anchor;
	float height;
	float width;
	float speed;
	float rotation;
	float frequency;
	float amplitude;
	bool isAlive;
};

#endif