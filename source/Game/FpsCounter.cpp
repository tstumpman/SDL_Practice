#include "FpsCounter.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_Rect.h"
#include "MoveComponent.h"
#include "MonospaceCharacter.h"
#include "InputComponent.h"
#include <string>

//Constructor
FpsCounter::FpsCounter(
	Game* game
) : TextChunk(game, game->getWindowSize() * 0.1f, 6, 1, "resources/monospace_alpha.png")
{
	timeSinceLastRender = 0.0f;
	framesSinceReset = 0;
	timeBetweenReset = 5.0f;
	timeBetweenRenders = 0.25f;
}

//Destructor
FpsCounter::~FpsCounter() {
}

void FpsCounter::actorInput(const uint8_t* keystate) {
}


void FpsCounter::updateActor(float deltaTime) {
	timeSinceLastRender += deltaTime;
	timeSinceLastReset += deltaTime;
	framesSinceReset++;

	if (timeSinceLastRender > timeBetweenRenders) {
		float fps = (float)framesSinceReset / timeSinceLastReset;
		std::string fpsString = std::to_string(fps);
		this->setText(fpsString);
		this->timeSinceLastRender = 0.0f;
	}

	if (timeSinceLastReset > timeBetweenReset) {
		timeSinceLastReset = 0.0f;
		framesSinceReset = 0;
	}
}