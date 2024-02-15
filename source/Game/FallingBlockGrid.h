#ifndef C_FALLING_BLOCK_GRID_H
#define C_FALLING_BLOCK_GRID_H
#include "game.h"
#include "Vector2D.h"
#include "CartesianCoordinate.h"
#include "Rect.h"
#include <string>
#include <vector>
struct SDL_Color;
struct SDL_Renderer;
struct SDL_Texture;
class FallingBlockGrid : public Actor {
public://Functions
	//Default constructor
	FallingBlockGrid(
		Game* game,
		Vector2D gridSize,
		CartesianCoordinate gridDimensions
	);

	//Destructor
	~FallingBlockGrid();

	virtual void updateActor(float deltaTime);
	void setPosition(Vector2D newPos) override;

	Vector2D getSize() const;
	CartesianCoordinate getGridDimensions() const;

	void setItem(CartesianCoordinate coord, Actor* item);
	void setItem(unsigned int index, Actor* item);
	Rect getBoundaryForItemSlot(CartesianCoordinate coord);
	Vector2D getCellSize() const;
	Vector2D getCellPosition(CartesianCoordinate coord) const;

private://functions
	FallingBlockGrid();
	Actor* getItemAt(unsigned int index);
	Actor* getItemAt(CartesianCoordinate index);
	std::vector<Rect> calculateLetterSlots(Rect boundary, unsigned int cols, unsigned int rows);
protected://functions
public: //Data
private://Data
	CartesianCoordinate getCoordinate(unsigned int index);
	unsigned int getIndex(CartesianCoordinate coordinate);
	CartesianCoordinate gridIndices;
	Vector2D gridSize;
	std::vector<Actor*> items;

protected://Data
};

#endif