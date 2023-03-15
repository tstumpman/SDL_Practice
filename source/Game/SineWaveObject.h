#ifndef SINE_WAVE_OBJECT
#define SINE_WAVE_OBJECT

class SDL_Renderer;
typedef unsigned __int8 uint8_t;
class SineWaveObject {
public: 
	SineWaveObject();
	void update(float deltaTime, float screenWidth, float screenHeight);
	void render(SDL_Renderer* renderer);
	void setEnabled(bool isEnabled);
	void resetAll(
		float startXPos,
		float startYPos,
		float anchor,
		float speed,
		float height,
		float width,
		float amplitude,
		float frequency,
		float lifetime,
		uint8_t colorR,
		uint8_t colorG,
		uint8_t colorB
	);
	bool getIsAlive();
private: //Functions
private:
	uint8_t colorR;
	uint8_t colorG;
	uint8_t colorB;
	float objPosX;
	float objPosY;
	float anchor;
	float height;
	float width;
	float speed;
	float rotation;
	float frequency;
	float lifetime;
	float elapsedTime;
	float amplitude;
	bool isAlive;
};

#endif